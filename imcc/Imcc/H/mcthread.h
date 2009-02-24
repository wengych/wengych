/*--------------------------------------------------------------------------*/
/*  MCTHREAD.h                                                              */
/*                                                                          */
/*  History                                                                 */
/*      11/28/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#ifndef __MCTHREAD_H__
#define __MCTHREAD_H__

#include "imccdef.h"

#if defined(LINUX) || defined(UNIX)
	#define INFINITE (uint32)-1
#endif

#ifdef WIN32
#include <winbase.h>
#endif

#if defined(UTIL_EXPORTS)
#define UTIL_EXPORT DLLEXPORT
#else
#define UTIL_EXPORT DLLIMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// class diagram
//
class MC_Critical_Section;
class MC_Lock;
class MC_Event;
class MC_Thread;

/////////////////////////////////////////////////////////////////////////////
// MC_Critical_Section
//
class UTIL_EXPORT MC_Critical_Section
{
public :
    MC_Critical_Section(boolean auto_init = TRUE);
    virtual ~MC_Critical_Section();

    virtual void init();
    virtual void cleanup();

    virtual void lock();
    virtual void unlock();
    virtual boolean trylock();

protected :
#if defined(WIN32)
    CRITICAL_SECTION m_cs;
#endif

#if defined(UNIX)
    pthread_mutex_t m_mutex;
#endif

	boolean m_auto_init;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Lock
//
class UTIL_EXPORT MC_Lock
{
public :
    MC_Lock(MC_Critical_Section &cs);
    virtual ~MC_Lock();

protected :
    MC_Critical_Section& m_cs_ref;
};

/////////////////////////////////////////////////////////////////////////////
// MC_Event
//
class UTIL_EXPORT MC_Event
{
public :
    MC_Event();
    virtual ~MC_Event();

public :
    boolean create();
    void set_event();
    void reset_event();

    boolean wait(uint32 time_out = INFINITE);

protected :
#ifdef WIN32
    HANDLE m_event_handle;
#endif

#ifdef UNIX
    pthread_mutex_t m_cv_mutex;
    pthread_cond_t  m_cv;
	int m_flag;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// MC_Thread
//
#ifdef WIN32
#define THREAD_HANDLE HANDLE
#endif

#ifdef UNIX
#define THREAD_HANDLE pthread_t
#endif

class UTIL_EXPORT MC_Thread
{
public :
    MC_Thread();
    virtual ~MC_Thread();

public :
    boolean create();
    boolean stop(uint32 time_out = INFINITE);
    boolean is_self_thread();

    THREAD_HANDLE get_thread_handle();
	uint32 get_thread_id();

public :
    virtual uint32 thread_run() = 0;

#ifdef WIN32
    static uint32 WINAPI thread_proc(void* param);
#endif

#ifdef UNIX
    static void* thread_proc(void* param);
    static void thread_cleanup_proc(void* param);
#endif

protected :
    THREAD_HANDLE	m_thread_handle;
	boolean			m_stop_flag;
	MC_Event		m_stop_event;

#ifdef WIN32
    uint32			m_thread_id;
#endif
};

#ifdef WIN32
/////////////////////////////////////////////////////////////////////////////
// WIN32 security utility function
//
#define DECLARE_SA(sa)      \
    SECURITY_ATTRIBUTES sa; \
    char pSD_##sa[SECURITY_DESCRIPTOR_MIN_LENGTH];  \
	sa.nLength = sizeof(sa);                        \
	sa.lpSecurityDescriptor = (PSECURITY_DESCRIPTOR)pSD_##sa; \
	sa.bInheritHandle = TRUE

boolean UTIL_EXPORT initialize_sa(SECURITY_ATTRIBUTES& sa);
#endif

#endif //__MCTHREAD_H__
