/*--------------------------------------------------------------------------*/
/*  MCLIST.H                                                                */
/*  Template Container Class: Array                                         */
/*                                                                          */
/*  History                                                                 */
/*      11/25/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCLIST_H__)
#define __MCLIST_H__

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

/////////////////////////////////////////////////////////////////////////////
//  MC_List
//
template <class _T> class MC_List
{
public :
	MC_List(int block_size = 64);
	virtual ~MC_List();

	void set_block_size(int block_size);
	int size() const;
	boolean empty() const;

	_T front();
	_T pop_front();
	void push_front(_T& value);

	_T back();
	_T pop_back();
	void push_back(_T& value);

	void insert_at(MC_POSITION& r_pos, _T& value);

	MC_POSITION begin() const;
	boolean next(MC_POSITION& r_pos, _T& r_value) const;
	void erase(MC_POSITION& r_pos);
	void remove_all();

protected :
	struct _Node
	{
		_Node*	next;
		_Node*	prev;
		_T		value;
	};

	_Node* new_node();
	void	free_node(_Node* node);

	_Node*	m_head;
	_Node*	m_tail;
	int		m_size;
	_Node*	m_free_list;

	struct	MC_Plex* m_blocks;
	int		m_block_size;
};

/////////////////////////////////////////////////////////////////////////////
// MC_List<_T> inline functions
//
template<class _T>
inline void MC_List<_T>::set_block_size(int block_size)
	{ m_block_size = block_size==0?32:block_size; }

template<class _T>
inline int MC_List<_T>::size() const { return m_size; }

template<class _T>
inline boolean MC_List<_T>::empty() const { return m_size==0; }

template<class _T>
inline _T MC_List<_T>::front()
{
	MC_ASSERT(m_size>0 && m_head != NULL);
	return m_head->value;
}

template<class _T>
inline _T MC_List<_T>::back()
{
	MC_ASSERT(m_size>0 && m_tail != NULL);
	return m_tail->value;
}

template<class _T>
inline MC_POSITION MC_List<_T>::begin() const
{ 
	return (m_size <= 0) ? NULL : MC_BEFORE_START_POSITION; 
}

/////////////////////////////////////////////////////////////////////////////
// MC_List<_T>
//
template<class _T>
MC_List<_T>::MC_List(int block_size)
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
	m_free_list = NULL;

	m_blocks = NULL;
	m_block_size = block_size;
}

template<class _T>
MC_List<_T>::~MC_List()
{
	remove_all();
}

template<class _T>
_T MC_List<_T>::pop_front()
{
	MC_ASSERT(m_size>0 && m_head != NULL);
	_Node* node = m_head;
	_T ret = node->value;
	m_head = node->next;
	if(m_head)
		m_head->prev = NULL;
	else
		m_tail = NULL;
	free_node(node);
	return ret;
}

template<class _T>
void MC_List<_T>::push_front(_T& value)
{
	_Node* node = new_node();
	MC_ASSERT(node);
	node->value = value;
	node->prev = NULL;
	node->next = m_head;
	if(m_head)
		m_head->prev = node;
	m_head = node;
	if(m_tail == NULL)
		m_tail = node;
}

template<class _T>
_T MC_List<_T>::pop_back()
{
	MC_ASSERT(m_size>0 && m_tail != NULL);
	_Node* node = m_tail;
	_T ret = node->value;
	m_tail = node->prev;
	if(m_tail)
		m_tail->next = NULL;
	else
		m_head = NULL;

	free_node(node);
	return ret;
}

template<class _T>
void MC_List<_T>::push_back(_T& value)
{
	_Node* node = new_node();
	MC_ASSERT(node);
	node->value = value;
	node->prev = m_tail;
	node->next = NULL;
	
	if(m_tail)
		m_tail->next = node;
	m_tail = node;
	if(m_head == NULL)
		m_head = node;
}

template<class _T>
boolean MC_List<_T>::next(MC_POSITION& r_pos, _T& r_value) const
{
	MC_ASSERT(m_size>0);

	_Node* ret_node = (_Node*)r_pos;
	MC_ASSERT(ret_node != NULL);

	if(ret_node == (_Node*) MC_BEFORE_START_POSITION)
		ret_node = m_head;
	else
		ret_node = ret_node->next;

	if(ret_node != NULL)
	{
		r_value = ret_node->value;
		r_pos = (MC_POSITION)ret_node;
		return TRUE;
	}
	else
	{
		r_pos = NULL;
		return FALSE;
	}
}

template<class _T>
void MC_List<_T>::erase(MC_POSITION& r_pos)
{
	MC_ASSERT(m_size>0);
	MC_ASSERT(r_pos != NULL);
	MC_ASSERT(r_pos != MC_BEFORE_START_POSITION);

	_Node* this_node = (_Node*)r_pos;
	_Node* prev_node = this_node->prev;
	_Node* next_node = this_node->next;

	if(prev_node == NULL)
	{
		m_head = next_node;
		if(m_head != NULL)
			r_pos = MC_BEFORE_START_POSITION;
		else
			r_pos = NULL;
	}
	else
	{
		prev_node->next = next_node;
		r_pos = (MC_POSITION)prev_node;
	}

	if(next_node == NULL)
		m_tail = prev_node;
	else
		next_node->prev = prev_node;

	free_node(this_node);
}

template<class _T>
void MC_List<_T>::insert_at(MC_POSITION& r_pos, _T& value)
{
	if(r_pos == MC_BEFORE_START_POSITION || (_Node*)r_pos == m_head)
	{
		push_front(value);
		r_pos = (MC_POSITION)m_head;
	}
	else if(r_pos == NULL)
	{
		push_back(value);
		r_pos = (MC_POSITION)m_tail;
	}
	else
	{
		_Node* tmp = (_Node*)r_pos;
		_Node* node = new_node();
		MC_ASSERT(node);
		node->value = value;
		node->prev = tmp->prev;
		node->prev->next = node;
		node->next = tmp;
		tmp->prev = node;

		r_pos = (MC_POSITION)node;
	}
}

template<class _T>
void MC_List<_T>::remove_all()
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
	m_free_list = NULL;

	if(m_blocks != NULL)
	{
		m_blocks->free_data_chain();
		m_blocks = NULL;
	}
}

template<class _T>
typename MC_List<_T>::_Node* MC_List<_T>::new_node()
{
	if(m_free_list == NULL)
	{
		if(m_block_size == 0)
			m_block_size = 32;

		MC_Plex* new_block = 
			MC_Plex::create(m_blocks, m_block_size, sizeof(MC_List::_Node));
		MC_List::_Node* node = (MC_List::_Node*) new_block->data();

		node += m_block_size - 1;
		for(int i = m_block_size-1; i >= 0; i--, node--)
		{
			node->next = m_free_list;
			m_free_list = node;
		}
	}
	MC_ASSERT(m_free_list != NULL);

	MC_List::_Node* node = m_free_list;
	m_free_list = m_free_list->next;
	m_size++;
	MC_ASSERT(m_size > 0);
	
	return node;
}

template<class _T>
void MC_List<_T>::free_node(_Node* node)
{
	node->next = m_free_list;
	m_free_list = node;
	m_size--;
	MC_ASSERT(m_size >= 0);

	if(m_size == 0)
		remove_all();
}

#endif //__MC_List_H__
