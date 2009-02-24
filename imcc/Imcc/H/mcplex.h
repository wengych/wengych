/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  MCPLEX.H                                                                */
/*                                                                          */
/*  History                                                                 */
/*      11/30/2003     created by Jack Feng                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPLEX_H__)
#define __MCPLEX_H__

#include "mcassert.h"

// abstract iteration position
struct __MC_POSITION { };
typedef __MC_POSITION* MC_POSITION;
#define MC_BEFORE_START_POSITION ((MC_POSITION)-1L)

/////////////////////////////////////////////////////////////////////////////
//  MC_Plex
//
struct MC_Plex
{
	MC_Plex * m_next;

	void* data()
	{ 
		return this+1; 
	}

	static MC_Plex* create(MC_Plex*& head, uint32 max, uint32 element_size)
	{
		MC_ASSERT(max > 0 && element_size > 0);

		MC_Plex* p = (MC_Plex*) new uint8[sizeof(MC_Plex) + max*element_size];

		p->m_next = head;
		head = p;
		return p;
	}

	void free_data_chain()
	{
		MC_Plex* p = this;

		while(p != NULL)
		{
			uint8* bytes = (uint8*)p;
			MC_Plex* next = p->m_next;
			delete [] bytes;
			p = next;
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
//  MC_Allocator
//
template <class _T> class MC_Allocator
{
public :
	MC_Allocator(int block_size);
	virtual ~MC_Allocator();

	_T* t_new();
	void t_free(_T* t);

	void init(int block_size);
	void clear();

protected :
	struct _Node
	{
		_T		value;
		_Node*	next;
	};

	struct MC_Plex*	m_plex_blocks;
	int		m_plex_block_size;
	uint32	m_plex_count;
	_Node*	m_plex_free_list;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Allocator<_T> functions
//
template<class _T>
MC_Allocator<_T>::MC_Allocator(int block_size = 32)
{
	init(block_size);
}

template<class _T>
MC_Allocator<_T>::~MC_Allocator()
{
	clear();
}

template<class _T>
_T* MC_Allocator<_T>::t_new()
{
	if(m_plex_free_list == NULL)
	{
		MC_ASSERT(m_plex_block_size>0);
		MC_Plex* new_block = 
			MC_Plex::create(m_plex_blocks, m_plex_block_size, 
			sizeof(_Node));
		_Node* node = (_Node*) new_block->data();

		node += m_plex_block_size - 1;
		for(int i = m_plex_block_size-1; i >= 0; i--, node--)
		{
			node->next = m_plex_free_list;
			m_plex_free_list = node;
		}
	}

	_Node* node = m_plex_free_list;
	m_plex_free_list = m_plex_free_list->next;
	m_plex_count++;

	return &(node->value);
}

template<class _T>
void MC_Allocator<_T>::t_free(_T* t)
{
	_Node* node = (_Node*)t;

	node->next = m_plex_free_list;
	m_plex_free_list = node;
	m_plex_count--;

	if(m_plex_count == 0)
	{
		m_plex_free_list = NULL;
		if(m_plex_blocks)
		{
			m_plex_blocks->free_data_chain();
			m_plex_blocks = NULL;
		}
	}
}

template<class _T>
void MC_Allocator<_T>::init(int block_size)
{
	m_plex_blocks = NULL;
	m_plex_block_size = block_size;
	m_plex_free_list = NULL;
	m_plex_count = 0;
}

template<class _T>
void MC_Allocator<_T>::clear()
{
	m_plex_free_list = NULL;
	if(m_plex_blocks)
	{
		m_plex_blocks->free_data_chain();
		m_plex_blocks = NULL;
	}
	m_plex_count = 0;
}

#endif //__MCPLEX_H__
