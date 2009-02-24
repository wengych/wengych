/*--------------------------------------------------------------------------*/
/*  MCTS.H                                                                  */
/*  Text stream encoder                                                     */
/*                                                                          */
/*  History                                                                 */
/*      11/29/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCTS_H__)
#define __MCTS_H__

#include "imccdef.h"
#include <stdio.h>

#if defined(UTIL_EXPORTS)
#define UTIL_API DLLEXPORT
#else
#if defined(URLPING)
#define UTIL_API 
#else
#define UTIL_API DLLIMPORT
#endif
#endif

#define MC_String MC_Text_Stream

/////////////////////////////////////////////////////////////////////////////
//  MC_Text_Stream
//
class UTIL_API MC_Text_Stream
{
public :
    typedef enum Ordix
    {
        hex     = 0,
        decimal = 1
    };

    typedef struct Bin
    {
        uint8*	data;
        uint16	len;
    };

public :
	MC_Text_Stream();
	MC_Text_Stream(const char* buf);
	MC_Text_Stream(char* buf, uint32 buf_size);
	MC_Text_Stream(uint32 buf_size, uint32 grow_by_size = 32);
	virtual ~MC_Text_Stream();

	operator char*() const;
	char& operator[](uint32 pos);
	uint32 length() const;
	uint32 raw_buf_size() const;
    boolean is_empty() const;
	void reset(boolean delete_buf = FALSE);
	void truncate(uint32 length);
	void rigth_trim();
	void left_trim();
	void trim();
	char* find_token(char* token);

	MC_Text_Stream& operator << (uint8 ch);
	MC_Text_Stream& operator << (char ch);
	MC_Text_Stream& operator << (int16 s);
	MC_Text_Stream& operator << (uint16 s);
	MC_Text_Stream& operator << (int s);
	MC_Text_Stream& operator << (unsigned int s);
	MC_Text_Stream& operator << (int32 l);
	MC_Text_Stream& operator << (uint32 l);
	MC_Text_Stream& operator << (float32 f);
	MC_Text_Stream& operator << (float64 d);
	MC_Text_Stream& operator << (char* str);
	MC_Text_Stream& operator << (const char str[]);
	MC_Text_Stream& operator << (void * lpv);
	MC_Text_Stream& operator << (Bin& bin);
	MC_Text_Stream& operator << (Ordix ordix);
	MC_Text_Stream& write(uint8* bin, uint16 bin_len);

	void grow(uint32 grow_size);

protected :
	char*	m_buf;
	uint32	m_cur_pos;
	uint32	m_buf_size;
	uint32	m_grow_size;
	boolean	m_is_hex_mode;
	boolean	m_need_delete_buf;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Text_Stream inline functions
//
inline MC_Text_Stream& MC_Text_Stream::operator << (uint8 ch)
{
	return *this << (int32)ch;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (char ch)
{
	return *this << (int32)ch;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (int16 s)
{
	return *this << (int32)s;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (uint16 s)
{
	return *this << (int32)s;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (int s)
{
	return *this << (int32)s;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (unsigned int s)
{
	return *this << (int32)s;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (const char str[])
{
	return *this << (char*)str;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (void * lpv)
{
	m_is_hex_mode = TRUE;
	return *this << (uint32)(INT_PTR)lpv;
}

inline MC_Text_Stream& MC_Text_Stream::operator << (Ordix ordix)
{
	switch(ordix)
	{
	case hex :
		m_is_hex_mode = TRUE;
		break;

	case decimal :
		m_is_hex_mode = FALSE;
		break;

	default :
		break;
	}

	return *this;
}

inline MC_Text_Stream::operator char*() const
{ 
	return m_buf; 
}

inline char& MC_Text_Stream::operator[](uint32 pos)
{
	return m_buf[pos];
}

inline uint32 MC_Text_Stream::length() const
{
	return m_cur_pos;
}

inline boolean MC_Text_Stream::is_empty() const
{
	return (m_cur_pos==0);
}

inline uint32 MC_Text_Stream::raw_buf_size() const
{
	return m_buf_size;
}

#endif //__MCTS_H__
