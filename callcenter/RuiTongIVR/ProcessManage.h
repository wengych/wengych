
#ifndef __PROCESS_MANAGE_
#define __PROCESS_MANAGE_

#include <string>
#include <vector>

class CProcessManage
{
public :

	//根据pid来判断进程是否存在
	//return:	0:错误 >0对应进程（由于pid为0是系统进程，因此创建的时候肯定不会返回0，返回-1的话，就不是dword类型了）
    static bool  IsProgramRunning(DWORD pid, std::string valid_process_name) ;
    static bool IsProgramRunning(const std::string& pid, std::string valid_process_name) ;
	//启动指定位置进程
	//return:	0:错误 >0对应进程（由于pid为0是系统进程，因此创建的时候肯定不会返回0）
	static  DWORD  StartProgram(std::string strFile);

	
};


#endif