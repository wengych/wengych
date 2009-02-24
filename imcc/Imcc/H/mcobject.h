/*--------------------------------------------------------------------------*/
/*  MCOBJECT.H                                                              */
/*  Most basic object                                                       */
/*                                                                          */
/*  History                                                                 */
/*      11/30/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#ifndef __MCOBJ_H__
#define __MCOBJ_H__

#include "mcthread.h"
#include "mcassert.h"

#ifndef __cplusplus
#error This IMCC basic facility can only be used in C++
#endif

#if defined(UTIL_EXPORTS)
#define UTIL_EXPORT DLLEXPORT
#else
#define UTIL_EXPORT DLLIMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Classes diagram
//
class MC_Object;
class MC_ObjectX;

//////////////////////////////////////////////////////////////////////////////
// MC_Object
//
#define MC_MAX_OBJ_KEY_LENGTH 32
#define MC_MAX_OBJ_CLASS_LENGTH 16

class UTIL_EXPORT MC_Object
{
public :
    MC_Object();
    virtual ~MC_Object();

    virtual void add_reference();
    virtual void release_reference();
    virtual void on_post_message(uint32 msg_type, void* msg_data) {}

	virtual void assert_valid();
	virtual void set_obj_key(char* obj_key);
	virtual char* get_obj_key();
	virtual void set_obj_class(char* obj_class);
	virtual char* get_obj_class();
	virtual uint16 get_ref_cnt();

protected :
	char m_obj_key[MC_MAX_OBJ_KEY_LENGTH];
	char m_obj_class[MC_MAX_OBJ_CLASS_LENGTH];
	uint16 m_magic;
    uint16 m_ref_cnt;
};

//////////////////////////////////////////////////////////////////////////////
// MC_ObjectX
//
class UTIL_EXPORT MC_ObjectX : public MC_Object
{
public :
    MC_ObjectX();
    virtual ~MC_ObjectX();

    virtual void add_reference();
    virtual void release_reference();

protected :
    MC_Critical_Section m_ref_cs;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Object inline functions
//
inline void MC_Object::add_reference() 
{ 
	m_ref_cnt++; 
}

inline void MC_Object::release_reference()
{
	m_ref_cnt--;
	if(m_ref_cnt == 0)
		delete this;
}

inline void MC_Object::assert_valid() 
{	MC_ASSERT(m_magic == 5621);	}	

inline char* MC_Object::get_obj_key() 
{ return m_obj_key; }

inline char* MC_Object::get_obj_class() 
{ return m_obj_class; }

inline uint16 MC_Object::get_ref_cnt() 
{ return m_ref_cnt; }

/////////////////////////////////////////////////////////////////////////////
// Utility macro
//
#define DECLARE_OBJECT_KEY(str)	\
{ \
	char tmp_dok_buf[MC_MAX_OBJ_KEY_LENGTH] = ""; \
	MC_Text_Stream dok_ts(tmp_dok_buf, MC_MAX_OBJ_KEY_LENGTH); \
	set_obj_key(dok_ts << str); \
}

#define DECLARE_OBJECT_CLASS(str)	set_obj_class(str);

#endif //__MCOBJ_H__
