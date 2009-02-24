/*--------------------------------------------------------------------------*/
/*  MCMISC.H                                                                */
/*  Miscellaneous functions                                                 */
/*  History                                                                 */
/*      11/30/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCMISC_H__)
#define __MCMISC_H__


#if defined(UTIL_EXPORTS)
#define UTIL_EXPORT DLLEXPORT
#else
#define UTIL_EXPORT DLLIMPORT
#endif

#define mc_abs(x1, x2) ((x1)>(x2)?((x1)-(x2)):((x2)-(x1)))

/** 
/* Miscellaneous functions
*/
#if defined(WIN32)
	#define get_tick_count GetTickCount
#else
	UTIL_EXPORT uint32 get_tick_count();
#endif

UTIL_EXPORT uint32 get_hr_tick_count();


inline uint32 get_tick_interval(uint32 start, uint32 end)
{
    if(end >= start)
        return end - start;

    return (uint32)-1 - start + 1 + end;
}

UTIL_EXPORT boolean simple_url_crack(char* url, 
	char* prot_type, uint16 max_len_of_prot_type, 
	char* host, uint16 max_len_of_host, int* port);
UTIL_EXPORT char* get_local_ip();
UTIL_EXPORT boolean is_local_ip(char* addr);
UTIL_EXPORT boolean is_ip(char* addr, boolean exp_star = FALSE);
UTIL_EXPORT boolean dns_2_ip(char* dns, char* ip);
UTIL_EXPORT uint32 ip_2_id(char* ip);
UTIL_EXPORT void byte_stream_swap(void* data, int length);

UTIL_EXPORT boolean config_read_key(uint8* value, uint32* value_len, char* key, 
	char* value_name, uint32 type_expected);
UTIL_EXPORT char* config_get_root_path();
UTIL_EXPORT void config_get_parameter_string(const char* section, 
	const char* key, const char* default_val, char* return_val, 
	uint32 size);
UTIL_EXPORT int config_get_parameter_int(const char* section, 
	const char* key, int default_val);
UTIL_EXPORT boolean config_set_parameter(const char* section, 
	const char* key, char* val);

UTIL_EXPORT char* xml_get_string(char* src, char* tag, int max_len, 
								 char* buf, char* def);
UTIL_EXPORT uint32 xml_get_uint(char* src, char* tag, uint32 def);
UTIL_EXPORT int xml_get_int(char* src, char* tag, int def);
UTIL_EXPORT char* url_str_encode(char* src, char* dest, int max_len);

UTIL_EXPORT char* string_new(char* str);
UTIL_EXPORT void string_trim_white_space(char** str, uint32* len);
UTIL_EXPORT void string_trim_quotes(char** str, uint32* len);
UTIL_EXPORT boolean string_get_delimited_token(char** src, uint32* src_len,
	char** tok, uint32* tok_len, char delim);
UTIL_EXPORT boolean string_get_key_value_pair(char* src, uint32 src_len,
	char** key, uint32* key_len, char** val, uint32* val_len);

#endif //__MCMISC_H__
