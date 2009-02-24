/*--------------------------------------------------------------------------*/
/*  MCSDP.H                                                                 */
/*  Utility: Shared Data Packet                                             */
/*                                                                          */
/*  History                                                                 */
/*      11/26/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCSDP_H__)
#define __MCSDP_H__

/**
/* Platform definition and platform specific definitions
*/
#include "imccdef.h"
#include "mcobject.h"

#ifndef __cplusplus
#error This IMCC basic facility can only be used in C++
#endif

#if defined(UTIL_EXPORTS)
#define UTIL_EXPORT DLLEXPORT
#else
#define UTIL_EXPORT DLLIMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Basic data buffers
//
typedef struct _MC_Buffers
{
	uint8*			data;
	uint32			data_length;
	_MC_Buffers*	next;
} MC_Buffers;

UTIL_EXPORT MC_Buffers* mc_allocate_buffers(uint16 data_length);
UTIL_EXPORT void mc_delete_buffers(MC_Buffers* buffers);

/////////////////////////////////////////////////////////////////////////////
// Classes diagram
//
class MC_Shared_Data_Packet;

/////////////////////////////////////////////////////////////////////////////
// MC_Shared_Data_Packet
//
class UTIL_EXPORT MC_Shared_Data_Packet : public MC_Object
{
public:
	MC_Shared_Data_Packet();
	virtual ~MC_Shared_Data_Packet();

	virtual uint8* allocate_buffer(uint16 raw_buffer_length);
	virtual void release_buffer();

	virtual void attach_data(uint8* data, uint16 raw_buffer_length);
	virtual void detach_data();

	virtual void set_data_length(uint16 data_len);
	virtual void set_offset(uint16 offset);
	virtual uint8* get_data();
	virtual uint16 get_data_length();
	virtual uint16 get_offset();

protected:
	uint8*	m_data;
	uint16	m_offset;
	uint16	m_data_length;
	uint16	m_raw_buffer_length;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Shared_Data_Packet inline functions
//
inline void MC_Shared_Data_Packet::set_data_length(uint16 data_len) 
{ m_data_length = data_len; }

inline void MC_Shared_Data_Packet::set_offset(uint16 offset) 
{ m_offset = offset; }

inline uint8* MC_Shared_Data_Packet::get_data() 
{ return m_data; }

inline uint16 MC_Shared_Data_Packet::get_data_length() 
{ return m_data_length; }

inline uint16 MC_Shared_Data_Packet::get_offset() 
{ return m_offset; }

#endif // __MCSDP_H__

