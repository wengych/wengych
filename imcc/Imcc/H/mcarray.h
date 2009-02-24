/*--------------------------------------------------------------------------*/
/*  MCARRAY.H                                                               */
/*  Template Container Class: Array                                         */
/*                                                                          */
/*  History                                                                 */
/*      11/25/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCARRAY_H__)
#define __MCARRAY_H__

#include "mcassert.h"

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
//  MC_Array
//
template <class _T> class MC_Array
{
public :
	MC_Array();
	virtual ~MC_Array();

	boolean set_size(int size);
	void set_growby(int growby);
	int size() const;
	boolean empty() const;

	_T get_at(int index) const;
	void set_at(int index, _T& new_element);
	_T& element_at(int index);

	int add(_T& element);
	int add_block(int block_size);
	void insert_at(int index, _T& element);
	void remove_at(int index);
	void remove_block(int index, int block_size);
	void remove_all();

	_T operator[] (int i) const;
	_T& operator[] (int i);

	void expand(int size);

protected :
	_T*		m_data;
	int		m_size;
	int		m_max_size;
	int		m_growby;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Array<_T> inline functions
//
template<class _T>
inline void MC_Array<_T>::set_growby(int growby) { m_growby = growby; }

template<class _T>
inline int MC_Array<_T>::size() const { return m_size; }

template<class _T>
inline boolean MC_Array<_T>::empty() const { return m_size==0; }

template<class _T>
inline _T MC_Array<_T>::get_at(int index) const
	{ MC_ASSERT(index >= 0 && index < m_size);
		return m_data[index]; }

template<class _T>
inline void MC_Array<_T>::set_at(int index, _T& new_element)
	{ MC_ASSERT(index >= 0 && index < m_size);
		m_data[index] = new_element; }

template<class _T>
inline _T& MC_Array<_T>::element_at(int index)
	{ MC_ASSERT(index >= 0 && index < m_size);
		return m_data[index]; }

template<class _T>
inline int MC_Array<_T>::add(_T& new_element)
	{ int index = m_size;
		insert_at(index, new_element);
		return index; }

template<class _T>
inline _T MC_Array<_T>::operator[](int index) const
	{ return get_at(index); }

template<class _T>
inline _T& MC_Array<_T>::operator[](int index)
	{ return element_at(index); }

/////////////////////////////////////////////////////////////////////////////
// MC_Array<_T>
//
template<class _T> 
MC_Array<_T>::MC_Array()
{
	m_size = m_max_size = 0;
	m_growby = 16;
	m_data = NULL;
}

template<class _T>
MC_Array<_T>::~MC_Array()
{
	if(m_data != NULL)
	{
		delete[] (uint8*)m_data;
		m_data = NULL;
		m_size = m_max_size = m_growby = 0;
	}
}

template<class _T>
boolean MC_Array<_T>::set_size(int size)
{
	if(size == 0)
	{
		m_size = m_max_size = size;

		if(m_data)
		{
			delete[] (uint8*)m_data;
			m_data = NULL;
		}
	}
	else if(m_max_size == 0)
	{
		m_size = m_max_size = size;

		if(m_data)
		{
			delete[] (uint8*)m_data;
			m_data = NULL;
		}

		m_data = (_T*) new uint8[m_max_size * sizeof(_T)];
		memset((uint8*)m_data, 0, m_max_size * sizeof(_T));
	}
	else if(m_max_size<size)
	{
		m_max_size = size;

		_T* new_data = (_T*) new uint8[m_max_size * sizeof(_T)];
		MC_ASSERT(new_data);
		memset((uint8*)new_data, 0, m_max_size * sizeof(_T));

		if(m_data)
		{
			if(m_size > 0)
				memcpy((uint8*)new_data, (uint8*)m_data, m_size * sizeof(_T));
			delete[] (uint8*)m_data;
		}
		
		m_data = new_data;
		m_size = m_max_size;
	}
	else if(m_max_size>size)
	{
		m_max_size = size;

		_T* new_data = (_T*) new uint8[m_max_size * sizeof(_T)];
		MC_ASSERT(new_data);
		memset((uint8*)new_data, 0, m_max_size * sizeof(_T));

		if(m_data)
		{
			if(m_size > 0)
				memcpy((uint8*)new_data, (uint8*)m_data, size * sizeof(_T));
			delete[] (uint8*)m_data;
		}
		
		m_data = new_data;
		m_size = m_max_size;
	}
	else //m_max_size==size
	{
		m_size = m_max_size;
	}
	
	return TRUE;
}

template<class _T>
int MC_Array<_T>::add_block(int block_size)
{
	if(m_size+block_size >= m_max_size)
		expand(m_size+block_size);

	memset((uint8*)m_data + m_size * sizeof(_T), 0, block_size * sizeof(_T));
	m_size += block_size;

	return m_size;
}

template<class _T>
void MC_Array<_T>::insert_at(int index, _T& new_element)
{
	MC_ASSERT(index >= 0);

	if(index>=m_max_size || (m_size+1)>=m_max_size)
		expand(m_size+1);

	if(index>=m_size)
	{
		m_data[index] = new_element;
	}
	else
	{
		memmove(&m_data[index+1], &m_data[index], (m_size-index)*sizeof(_T));
		m_data[index] = new_element;
	}

	m_size++;
}

template<class _T>
void MC_Array<_T>::remove_at(int index)
{
	MC_ASSERT(index >= 0);
	MC_ASSERT(index < m_size);

	int move_size = m_size-index;
	if(move_size > 1)
		memmove(&m_data[index], &m_data[index + 1],	move_size * sizeof(_T));
	
	memset((uint8*)&m_data[m_size-1], 0,  sizeof(_T));
	m_size --;
}

template<class _T>
void MC_Array<_T>::remove_block(int index, int block_size)
{
	MC_ASSERT(index >= 0);
	MC_ASSERT(index + block_size <= m_size);

	uint32 move_size = m_size - index + 1 - block_size;
	if(move_size > 1)
		memmove(&m_data[index], &m_data[index + block_size], move_size * sizeof(_T));
	
	memset((uint8*)&m_data[m_size-block_size], 0, block_size * sizeof(_T));
	m_size -= block_size;
}

template<class _T>
void MC_Array<_T>::remove_all() 
{ 
	if(m_data != NULL)
	{
		delete[] (uint8*)m_data;
		m_data = NULL;
		m_size = m_max_size = 0;
	}
}

template<class _T>
void MC_Array<_T>::expand(int size)
{
	MC_ASSERT(m_size <= m_max_size);
	while(m_max_size <= size)
		m_max_size += m_growby;

	_T* new_data = (_T*) new uint8[m_max_size * sizeof(_T)];
	MC_ASSERT(new_data);
	memset((uint8*)new_data, 0, m_max_size * sizeof(_T));

	if(m_data)
	{
		if(m_size > 0)
			memcpy((uint8*)new_data, (uint8*)m_data, m_size * sizeof(_T));
		delete[] (uint8*)m_data;
	}
	
	m_data = new_data;
}

#endif //__MCARRAY_H__
