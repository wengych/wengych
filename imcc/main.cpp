#include "stdafx.h"

#include "Conference.h"
#include "imcc/h/mcnc.h"

#include <atlbase.h>
#include "wtl80/atlapp.h"

typedef std::map<string, string> StringMap;
typedef StringMap::iterator StringMapIterator;

void ConnectServer(StringMap& argMap)
{
	// 初始化
	IMCC_Error err = IMCC_ERROR_SUCCESS;
	HINSTANCE hInst = (HINSTANCE)GetCurrentProcess();
	cout << "Current Process: " << hInst << '\n';
	err = MC_Node_Controller::initialize(hInst, IMCC_DEV_PC, IMCC_OS_WIN2k, IMCC_Net_Link_DSL);
	if (err != IMCC_ERROR_SUCCESS)
		throw std::runtime_error("imcc_error");
	cout << "MC_Node_Controller::initialize success!\n";

	// 创建会议管理对象
	MC_Conference_Mgr conf_mgr;
	conf_mgr.initialize();
	cout << "conf_mgr.initialize()\n";

	CConference conf(&conf_mgr);

	// 初始化site_id，从字符串转换而来
	uint32	site_id;
	{
		StringMapIterator it = argMap.find(_T("site_id"));
		if (it == argMap.end())
			throw std::runtime_error("parameter [site_id] not found!");

		string& temp = it->second;
		int nLen = temp.length();
		for(int i = 0 ;i < nLen && i < 4 ;i++)
			((PBYTE)&site_id)[i] =  (BYTE)temp.at(i);
	}
	char* site_url = "http://www.sina.com";
	uint32 conf_id = 70;
	char* conf_name = "test";
	char* user_name = "user";
	uint32 user_log_id = 10;
	DWORD dwCapability = 0;
	boolean bPublic = TRUE;
/*
	string server_ip;
	{
		StringMapIterator it = argMap.find(_T("server_ip"));
		if (it == argMap.end())
			throw std::runtime_error("parameter [server_ip] not fount!");

		server_ip = it->second;
		cout << "server_ip is " << server_ip << '\n';
	}
*/
	char* server_ip = "192.168.11.132";
	uint8					def_session_num = 0;
	MC_Conf_Session_Record*	def_session_list = NULL;
	uint8					def_object_num = 0;
	IMCC_Reg_Object**		def_object_list = NULL;
	uint16					auth_ticket_len = 16;
	uint8					auth_ticket[16];
	ZeroMemory(auth_ticket, 16);

	int nRet = conf.join_request(site_id, site_url, conf_id, conf_name,
				user_name, user_log_id, dwCapability, bPublic, server_ip,
				def_session_num, def_session_list,
				def_object_num, def_object_list,
				auth_ticket_len, auth_ticket);
	cout << "conf.join_request returns " << nRet << '\n';
}

int main(int argc, TCHAR **argv)
{
	try {
		StringMap argMap;		///< 存储命令行参数的集合

		// 循环读入所有参数
		for (int i = 1; i < argc; ++i) {
			size_t length = _tcslen(argv[i]);
			TCHAR* start = std::find(argv[i], argv[i]+length, _T('/'));
			TCHAR* colon = std::find(argv[i], argv[i]+length, _T(':'));
			if (start == argv[i]+length ||
				colon == argv[i]+length)
				throw std::out_of_range("参数格式错误");

			argMap.insert(std::make_pair(string(start+1, colon),
				string(colon+1, argv[i]+length)));
		}

		for (StringMapIterator it = argMap.begin();
			it != argMap.end(); ++it)
		{
			cout << it->first << '\t' << it->second << '\n';
		}

		ConnectServer(argMap);

		WTL::CMessageLoop msg_loop;
		msg_loop.Run();
	} catch(std::exception& ex) {
		std::cerr << ex.what() << '\n';
	}
	return 0;
}
