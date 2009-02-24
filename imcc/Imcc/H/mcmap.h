/*--------------------------------------------------------------------------*/
/*  MCMAP.H                                                                 */
/*  Template Container Class: Map                                           */
/*                                                                          */
/*  History                                                                 */
/*      11/25/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCMAP_H__)
#define __MCMAP_H__

#include "mcplex.h"

// 2008-01-29
// wengyc
// Deal with problem occured by _CRT_DEBUG_NEW
#ifndef _GNET_NO_DEBUG_NEW

#ifdef _DEBUG
#include <crtdbg.h>
#define new _CRT_DEBUG_NEW
#define _CRT_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif // _GNET_NO_DEBUG_NEW


template<class KEY> inline uint32 hash_key(KEY key)
{
	return ((uint32)(void*)(uint32)key) >> 4;
}

/////////////////////////////////////////////////////////////////////////////
//  MC_Map
//
template<class KEY, class VALUE> class MC_Map
{
public :
	MC_Map(int block_size = 64);
	virtual ~MC_Map();

	void set_block_size(int block_size);
	int size() const;
	boolean empty() const;

	boolean lookup(KEY key, VALUE& r_value) const;

	VALUE& operator[](KEY key);

	void set_at(KEY key, VALUE new_value);

	boolean remove_key(KEY key);
	void remove_all();
												
	MC_POSITION begin() const;
	void next(MC_POSITION& r_next_pos, KEY& r_key, VALUE& r_value) const;

	uint32 get_hash_table_size() const;
	void init_hash_table(uint32 hash_size, boolean alloc_now = TRUE);

protected :
	struct _Node
	{
		_Node*	next;
		uint32	hash_value;
		KEY		key;
		VALUE	value;
	};

	_Node*	new_node();
	void	free_node(_Node* node);
	_Node*	get_node_at(KEY key, uint32& hash) const;

	_Node**	m_hash_table;
	uint32	m_hash_table_size;
	int		m_size;
	_Node*	m_free_list;

	struct	MC_Plex* m_blocks;
	int		m_block_size;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Map<KEY, VALUE> inline functions
//
template<class KEY, class VALUE>
inline void MC_Map<KEY, VALUE>::set_block_size(int block_size)
	{ m_block_size = block_size==0?64:block_size; }

template<class KEY, class VALUE>
inline int MC_Map<KEY, VALUE>::size() const
	{ return m_size; }

template<class KEY, class VALUE>
inline boolean MC_Map<KEY, VALUE>::empty() const
	{ return m_size == 0; }

template<class KEY, class VALUE>
inline void MC_Map<KEY, VALUE>::set_at(KEY key, VALUE new_value)
	{ (*this)[key] = new_value; }

template<class KEY, class VALUE>
inline MC_POSITION MC_Map<KEY, VALUE>::begin() const
	{ return (m_size == 0) ? NULL : MC_BEFORE_START_POSITION; }

template<class KEY, class VALUE>
inline uint32 MC_Map<KEY, VALUE>::get_hash_table_size() const
	{ return m_hash_table_size; }

//template<class KEY, class VALUE>
//inline uint32 MC_Map<KEY, VALUE>::hash_key(KEY key)
//	{ return ((uint32)(void*)(uint32)key) >> 4; }

/////////////////////////////////////////////////////////////////////////////
// MC_Map<KEY, VALUE> out-of-line functions
//
template<class KEY, class VALUE>
MC_Map<KEY, VALUE>::MC_Map(int block_size)
{
	MC_ASSERT(block_size > 0);

	m_hash_table = NULL;
	m_hash_table_size = 17;  // default size
	m_size = 0;
	m_free_list = NULL;
	m_blocks = NULL;
	m_block_size = block_size;
}

template<class KEY, class VALUE>
void MC_Map<KEY, VALUE>::init_hash_table(
	uint32 hash_size, boolean alloc_now)
{
	MC_ASSERT(m_size == 0);
	MC_ASSERT(hash_size > 0);

	if(m_hash_table != NULL)
	{
		delete[] m_hash_table;
		m_hash_table = NULL;
	}

	if(alloc_now)
	{
		m_hash_table = new _Node* [hash_size];
		memset(m_hash_table, 0, sizeof(_Node*) * hash_size);
	}

	m_hash_table_size = hash_size;
}

template<class KEY, class VALUE>
void MC_Map<KEY, VALUE>::remove_all()
{
	if(m_hash_table != NULL)
	{
		delete[] m_hash_table;
		m_hash_table = NULL;
	}

	m_size = 0;
	m_free_list = NULL;

	if(m_blocks != NULL)
	{
		m_blocks->free_data_chain();
		m_blocks = NULL;
	}
}

template<class KEY, class VALUE>
MC_Map<KEY, VALUE>::~MC_Map()
{
	remove_all();
}

template<class KEY, class VALUE>
typename MC_Map<KEY, VALUE>::_Node*
MC_Map<KEY, VALUE>::new_node()
{
	if(m_free_list == NULL)
	{
		MC_ASSERT(m_block_size>0);
		MC_Plex* new_block = 
			MC_Plex::create(m_blocks, m_block_size, sizeof(MC_Map::_Node));
		MC_Map::_Node* node = (MC_Map::_Node*) new_block->data();

		node += m_block_size - 1;
		for(int i = m_block_size-1; i >= 0; i--, node--)
		{
			node->next = m_free_list;
			m_free_list = node;
		}
	}
	MC_ASSERT(m_free_list != NULL);

	MC_Map::_Node* node = m_free_list;
	m_free_list = m_free_list->next;
	m_size++;
	MC_ASSERT(m_size > 0);
	
	return node;
}

template<class KEY, class VALUE>
typename void MC_Map<KEY, VALUE>::free_node(_Node* node)
{
	node->next = m_free_list;
	m_free_list = node;
	m_size--;
	MC_ASSERT(m_size >= 0);

	if(m_size == 0)
		remove_all();
}

template<class KEY, class VALUE>
typename MC_Map<KEY, VALUE>::_Node*
MC_Map<KEY, VALUE>::get_node_at(KEY key, uint32& hash) const
{
	hash = hash_key<KEY>(key) % m_hash_table_size;

	if(m_hash_table == NULL)
		return NULL;

	_Node* node;
	for(node = m_hash_table[hash]; node != NULL; node = node->next)
	{
		if(node->key == key) return node;
	}

	return NULL;
}

template<class KEY, class VALUE>
boolean MC_Map<KEY, VALUE>::lookup(KEY key, VALUE& r_value) const
{
	uint32 hash;
	_Node* node = get_node_at(key, hash);
	if(node == NULL)
		return FALSE;

	r_value = node->value;

	return TRUE;
}

template<class KEY, class VALUE>
VALUE& MC_Map<KEY, VALUE>::operator[](KEY key)
{
	uint32 hash;
	_Node* node;
	if((node = get_node_at(key, hash)) == NULL)
	{
		if(m_hash_table == NULL)
			init_hash_table(m_hash_table_size);

		node = new_node();
		node->hash_value = hash;
		node->key = key;
		node->next = m_hash_table[hash];
		m_hash_table[hash] = node;
	}

	return node->value;
}

template<class KEY, class VALUE>
boolean MC_Map<KEY, VALUE>::remove_key(KEY key)
{
	if (m_hash_table == NULL)
		return FALSE;

	_Node** node_prev;
	node_prev = &m_hash_table[hash_key<KEY>(key) % m_hash_table_size];

	_Node* node;
	for(node = *node_prev; node != NULL; node = node->next)
	{
		if(node->key == key)
		{
			*node_prev = node->next;
			free_node(node);
			return TRUE;
		}

		node_prev = &node->next;
	}

	return FALSE;
}

template<class KEY, class VALUE>
void MC_Map<KEY, VALUE>::next(MC_POSITION& r_next_pos,
	KEY& r_key, VALUE& r_value) const
{
	MC_ASSERT(m_hash_table != NULL);

	_Node* ret_node = (_Node*)r_next_pos;
	MC_ASSERT(ret_node != NULL);

	if(ret_node == (_Node*) MC_BEFORE_START_POSITION)
	{
		for(uint32 bucket = 0; bucket < m_hash_table_size; bucket++)
			if((ret_node = m_hash_table[bucket]) != NULL)
				break;

		MC_ASSERT(ret_node != NULL);
	}

	_Node* node_next = NULL;
	if((node_next = ret_node->next) == NULL)
	{
		for(uint32 bucket = ret_node->hash_value + 1;
		  bucket < m_hash_table_size; bucket++)
			if((node_next = m_hash_table[bucket]) != NULL)
				break;
	}

	r_next_pos = (MC_POSITION) node_next;
	r_key = ret_node->key;
	r_value = ret_node->value;
};


#endif //__MCMAP_H__
