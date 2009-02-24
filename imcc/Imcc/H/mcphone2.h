/*--------------------------------------------------------------------------*/
/*  MCPHONE2.H                                                              */
/*                                                                          */
/*  History                                                                 */
/*      03/14/2006     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2006 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCPHONE2_H__)
#define __MCPHONE2_H__

//////////////////////////////////////////////////////////////////////////////
// MC_Phone2_Event_Handler
//
class MC_Phone2_Event_Handler
{
public :
	virtual int on_phone2_conf_join_cfm(int result) = 0;
	
	virtual int on_phone2_conf_leave_ind(int reason) = 0;

	virtual int on_phone2_conf_leave_cfm() = 0;

	virtual int on_phone2_audio_data_ind(unsigned long data_len, unsigned char* data) = 0;

	virtual int on_phone2_speak_req(unsigned short user_id, boolean enable_speak) = 0;

	virtual int on_phone2_kickoff_req(unsigned short user_id) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MC_Phone2_Conf
//
class MC_Phone2_Conf
{
public :
	virtual int destroy() = 0;

	virtual int phone2_conf_join(char *site_id, unsigned long conf_id, char* svr_ip) = 0;
	
	virtual int phone2_conf_leave() = 0;

	virtual int add_user(unsigned short  user_id, char* user_name, boolean speak_status) = 0;

	virtual int remove_user(unsigned short  user_id) = 0;

	virtual int change_user_speak_status(unsigned short  user_id, boolean speak_status) = 0;

	virtual int send_audio_data(unsigned long data_len, unsigned char* data) = 0;
};

//////////////////////////////////////////////////////////////////////////////
// mc_create_phone2_conf
//
extern "C" MC_Phone2_Conf* mc_phone2_conf_create(MC_Phone2_Event_Handler* handler);

#endif /* __MCPHONE2_H__ */
