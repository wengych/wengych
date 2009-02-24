/*--------------------------------------------------------------------------*/
/*  MCREF.H                                                                 */
/*                                                                          */
/*  Version 0.1(11/24/2003 refered on IMTC MCS API specificaiton 0.10)		*/
/*                                                                          */
/*  History                                                                 */
/*      11/24/2003     created by Jack Feng                                 */
/*                                                                          */
/*  Copyright (C) 2003 by CenWave Communications Inc.                       */
/*  All rights reserved                                                     */
/*--------------------------------------------------------------------------*/

#if !defined(__MCREF_H__)
#define __MCREF_H__

#include "imccdef.h"
#include "imcccore.h"
#include "mcutil.h"

//////////////////////////////////////////////////////////////////////////////
// inline utilities
// 
inline MC_Byte_Stream& operator<<(MC_Byte_Stream& os, IMCC_Result& result)
{
	os << (uint8)result;
	return os;
}

inline MC_Byte_Stream& operator>>(MC_Byte_Stream& is, IMCC_Result& result)
{
	uint8 tmp;
	is >> tmp;
	result = (IMCC_Result)tmp;
	return is;
}

inline MC_Byte_Stream& operator<<(MC_Byte_Stream& os, IMCC_Priority& priority)
{
	os << (uint8)priority;
	return os;
}

inline MC_Byte_Stream& operator>>(MC_Byte_Stream& is, IMCC_Priority& priority)
{
	uint8 tmp;
	is >> tmp;
	priority = (IMCC_Priority)tmp;
	return is;
}

inline MC_Byte_Stream& operator << (MC_Byte_Stream& os, IMCC_User_Data* user_data)
{
	os<<user_data->data_length;
	os.write(user_data->data, user_data->data_length);
	return os;
}

inline MC_Byte_Stream& operator >> (MC_Byte_Stream& is, IMCC_User_Data* user_data)
{
	is>>user_data->data_length;
	user_data->data = new uint8[user_data->data_length];
	MC_ASSERT(user_data->data);
	is.read(user_data->data, user_data->data_length);
	return is;
}

inline uint32 estimate_encode_size(IMCC_User_Data* user_data)
{
	return (user_data->data_length + 4);
}

inline MC_Byte_Stream& operator << (MC_Byte_Stream& os, IMCC_User_Data_1* user_data)
{
	os<<user_data->data_name << user_data->data_length;
	os.write(user_data->data, user_data->data_length);
	return os;
}

inline MC_Byte_Stream& operator >> (MC_Byte_Stream& is, IMCC_User_Data_1* user_data)
{
	is.read_string(user_data->data_name, IMCC_MAX_USER_DATA_NAME_LEN);
	is>>user_data->data_length;
	user_data->data = new uint8[user_data->data_length];
	MC_ASSERT(user_data->data);
	is.read(user_data->data, user_data->data_length);
	return is;
}

inline uint32 estimate_encode_size(IMCC_User_Data_1* user_data)
{
	return (uint32)(user_data->data_length + 8 + strlen(user_data->data_name));
}

inline MC_Byte_Stream& operator << (MC_Byte_Stream& os, IMCC_User_Data_2* user_data)
{
	os << user_data->data_index << user_data->data_length;

	os.write(user_data->data, user_data->data_length);
	return os;
}

inline MC_Byte_Stream& operator >> (MC_Byte_Stream& is, IMCC_User_Data_2* user_data)
{
	is >> user_data->data_index >> user_data->data_length;

	user_data->data = is.get_data() + is.tell();
	is.skip(user_data->data_length);
	//new uint8[user_data->data_length];
	//MC_ASSERT(user_data->data);
	//is.read(user_data->data, user_data->data_length);
	return is;
}

inline uint32 estimate_encode_size_ud2(IMCC_User_Data_2* user_data)
{
	return (user_data->data_length + 8);
}

inline MC_Byte_Stream& operator << (MC_Byte_Stream& os, IMCC_Table_Record* record)
{
	os << record->record_id << record->record_tag << record->record_fields_count;
	for(int i=0; i<record->record_fields_count; i++)
		os<<(&record->record_fields[i]);
	return os;
}

inline MC_Byte_Stream& operator >> (MC_Byte_Stream& is, IMCC_Table_Record* record)
{
	is >> record->record_id >> record->record_tag >> record->record_fields_count;

	if(record->record_fields_count > 0)
	{
		record->record_fields = new IMCC_User_Data[record->record_fields_count];
		MC_ASSERT(record->record_fields);

		for(int i=0; i<record->record_fields_count; i++)
			is >> (&record->record_fields[i]);
	}

	return is;
}

inline uint32 estimate_encode_size_tr(IMCC_Table_Record* record)
{
	uint32 size = 12;
	for(int i=0; i<record->record_fields_count; i++)
		size += estimate_encode_size(&record->record_fields[i]);
	return size;
}

inline void copy_tr(IMCC_Table_Record* dest, IMCC_Table_Record* src)
{
	*dest = *src;
	src->record_fields_count = 0;
	src->record_fields = NULL;
}

inline void delete_tr(IMCC_Table_Record* record)
{
	if(record->record_fields)
	{
		for(int i=0; i<record->record_fields_count; i++)
		{
			if(record->record_fields[i].data)
				delete [] record->record_fields[i].data;
		}

		delete [] record->record_fields;
		record->record_fields = NULL;
		record->record_fields_count = 0;
	}

	record->record_id = 0;
}

inline MC_Byte_Stream& operator << (MC_Byte_Stream& os, IMCC_Queue_Item* item)
{
	os << item->item_sender_id << item->item_sequence_number << item->item_tag;
	os << item->item_data_length;
	os.write(item->item_data, item->item_data_length);

	return os;
}

inline MC_Byte_Stream& operator >> (MC_Byte_Stream& is, IMCC_Queue_Item* item)
{
	is >> item->item_sender_id >> item->item_sequence_number >> item->item_tag;
	is >> item->item_data_length;
	if(item->item_data_length > 0)
	{
		item->item_data = new uint8[item->item_data_length];
		MC_ASSERT(item->item_data);
		is.read(item->item_data, item->item_data_length);
	}
	else
		item->item_data = NULL;

	return is;
}

inline uint32 estimate_encode_size_qi(IMCC_Queue_Item* item)
{
	return (uint32)(16 + item->item_data_length);
}

inline void copy_qi(IMCC_Queue_Item* dest, IMCC_Queue_Item* src)
{
	*dest = *src;
	if(dest->item_data_length>0)
	{
		dest->item_data = new uint8[dest->item_data_length];
		MC_ASSERT(dest->item_data);
		memcpy(dest->item_data, src->item_data, dest->item_data_length);
	}
}

inline void delete_qi(IMCC_Queue_Item* item)
{
	if(item->item_data)
	{
		delete [] item->item_data;
		item->item_data = NULL;
		item->item_data_length = 0;
	}
}

#endif // __MCREF_H__