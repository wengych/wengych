/*--------------------------------------------------------------------------*/
/*  MCBS.H                                                                  */
/*  Byte order stream encoder                                               */
/*                                                                          */
/*  History                                                                 */
/*      11/29/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCBS_H__)
#define __MCBS_H__

#include "imccdef.h"

typedef enum {
	MC_UNKNOWN_ENDIAN = 0,
	MC_LITTLE_ENDIAN = 1,
	MC_BIG_ENDIAN = 2,
} MC_Byte_Endian_Type;

/////////////////////////////////////////////////////////////////////////////
//  MC_Byte_Stream
//
class MC_Byte_Stream
{
public :
	MC_Byte_Stream(uint8* buf, uint32 offset, uint32 buf_size);
	virtual ~MC_Byte_Stream();

	void set_buffer(uint8* buf, uint32 offset, uint32 buf_size);
	uint32 seek(uint32 pos);
	uint32 skip(int32 dis);
	uint32 tell();
	uint8* get_data();
	void write(void* data, uint32 length);
	void read(void* data, uint32 length);
	MC_Byte_Stream& operator << (uint8 ch);
	MC_Byte_Stream& operator << (char ch);
	MC_Byte_Stream& operator << (int16 s);
	MC_Byte_Stream& operator << (uint16 s);
	MC_Byte_Stream& operator << (int32 l);
	MC_Byte_Stream& operator << (uint32 l);
	MC_Byte_Stream& operator << (float32 f);
	MC_Byte_Stream& operator << (float64 d);
	MC_Byte_Stream& operator << (char* str);
	MC_Byte_Stream& operator << (const char str[]);

	MC_Byte_Stream& operator >> (uint8& ch);
	MC_Byte_Stream& operator >> (char& ch);
	MC_Byte_Stream& operator >> (int16& s);
	MC_Byte_Stream& operator >> (uint16& s);
	MC_Byte_Stream& operator >> (int32& l);
	MC_Byte_Stream& operator >> (uint32& l);
	MC_Byte_Stream& operator >> (float32& f);
	MC_Byte_Stream& operator >> (float64& d);

	void read_string(const char str[], uint16 max_len);
	void read_string(char* & str, uint16 max_len);

protected :
	uint8* m_buf;
	uint32 m_cur_pos;
	uint32 m_buf_size;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Byte_Stream inline functions
//
inline MC_Byte_Stream::MC_Byte_Stream(uint8* buf, uint32 offset, uint32 buf_size)
{
	MC_ASSERT(buf);
	MC_ASSERT(buf_size>0);

	m_buf = buf;
	m_cur_pos = offset;
	m_buf_size = buf_size;
}

inline MC_Byte_Stream::~MC_Byte_Stream()
{
}

inline void MC_Byte_Stream::set_buffer(uint8* buf, uint32 offset, uint32 buf_size)
{
	MC_ASSERT(buf);
	MC_ASSERT(buf_size>0);

	m_buf = buf;
	m_cur_pos = offset;
	m_buf_size = buf_size;
}

inline uint32 MC_Byte_Stream::seek(uint32 pos)
{
	MC_ASSERT(pos<=m_buf_size);
	m_cur_pos = pos;
	return m_cur_pos;
}

inline uint32 MC_Byte_Stream::skip(int32 dis)
{
	MC_ASSERT(dis+m_cur_pos<=m_buf_size);
	m_cur_pos += dis;
	return m_cur_pos;
}

inline uint32 MC_Byte_Stream::tell()
{
	return m_cur_pos;
}

inline uint8* MC_Byte_Stream::get_data()
{
	return m_buf;
}

inline void MC_Byte_Stream::write(void* data, uint32 length)
{
	if(length == 0) return;

	MC_ASSERTX(length+m_cur_pos<=m_buf_size);

	memmove((uint8*)m_buf + m_cur_pos, (uint8*)data, length);
	m_cur_pos += length;
}

inline void MC_Byte_Stream::read(void* data, uint32 length)
{
	if(length == 0) return;

	MC_ASSERTX(length+m_cur_pos<=m_buf_size);

	memcpy((uint8*)data, m_buf + m_cur_pos, length);
	m_cur_pos += length;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (uint8 ch)
{
	write(&ch, sizeof(uint8));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (char ch)
{
	write(&ch, sizeof(char));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (int16 s)
{
	byte_stream_swap(&s, sizeof(int16));
	write(&s, sizeof(int16));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (uint16 s)
{
	byte_stream_swap(&s, sizeof(uint16));
	write(&s, sizeof(uint16));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (int32 l)
{
	byte_stream_swap(&l, sizeof(int32));
	write(&l, sizeof(int32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (uint32 l)
{
	byte_stream_swap(&l, sizeof(uint32));
	write(&l, sizeof(uint32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (float32 f)
{
	byte_stream_swap(&f, sizeof(float32));
	write(&f, sizeof(float32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (float64 d)
{
	byte_stream_swap(&d, sizeof(float64));
	write(&d, sizeof(float64));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (char* str)
{
	if(str)
	{
		uint16 len = (uint16)strlen(str);
		(*this) << len;
		if(len > 0) write((void*)str, len);
	}
	else
	{
		uint16 len = 0;
		(*this) << len;
	}

	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator << (const char str[])
{
	return (*this) << (char*)str;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (uint8& ch)
{
	MC_ASSERTX(m_cur_pos+1<=m_buf_size);

	ch = m_buf[m_cur_pos++];

	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (char& ch)
{
	MC_ASSERTX(m_cur_pos+1<=m_buf_size);

	ch = (char)m_buf[m_cur_pos++];

	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (int16& s)
{
	read(&s, sizeof(int16));
	byte_stream_swap(&s, sizeof(int16));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (uint16& s)
{
	read(&s, sizeof(uint16));
	byte_stream_swap(&s, sizeof(uint16));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (int32& l)
{
	read(&l, sizeof(int32));
	byte_stream_swap(&l, sizeof(int32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (uint32& l)
{
	read(&l, sizeof(uint32));
	byte_stream_swap(&l, sizeof(uint32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (float32& f)
{
	read(&f, sizeof(float32));
	byte_stream_swap(&f, sizeof(float32));
	return *this;
}

inline MC_Byte_Stream& MC_Byte_Stream::operator >> (float64& d)
{
	read(&d, sizeof(float64));
	byte_stream_swap(&d, sizeof(float64));
	return *this;
}

inline void MC_Byte_Stream::read_string(const char str[], uint16 max_len)
{
	uint16 len = 0;
	(*this) >> len;

	MC_ASSERTX(len <= max_len);
	MC_ASSERT(str);

	if(len > 0)
	{
		read((void*)str, len);
		((uint8*)str)[len] = 0;
	}
	else ((uint8*)str)[0] = 0;
}

inline void MC_Byte_Stream::read_string(char* & str, uint16 max_len)
{
	uint16 len = 0;
	(*this) >> len;

	MC_ASSERTX(len <= max_len);

	if(len > 0)
	{
		if(str)
		{
			read((void*)str, len);
			str[len] = 0;
		}
		else
		{
			str = new char[len + 1];
			MC_ASSERTX(str);
			read((void*)str, len);
			str[len] = 0;
		}
	}
	else if(str) str[0] = 0;
}

#endif //__MCBS_H__
