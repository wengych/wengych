#include "stdafx.h"
#include "ProcessManage.h"
#include "TinyXmlHelper.hpp"
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <Psapi.h>

#pragma comment(lib, "psapi")

using namespace helper;

//////////////////////////////////////////////////////////////////////////
bool CProcessManage::IsProgramRunning(const std::string& pid, std::string valid_process_name) 
{
    return IsProgramRunning(boost::lexical_cast<DWORD>(pid), valid_process_name);
}


bool CProcessManage::IsProgramRunning(DWORD pid, std::string valid_process_name) 
{
    if (pid < 0)
        return false;
    char path[MAX_PATH] = "";

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid );
    if (!hProcess)
        return false;

    HMODULE hModule;
    DWORD needed;
    EnumProcessModules(hProcess, &hModule, sizeof(hModule), &needed);
    GetModuleFileNameEx(hProcess, hModule, path, sizeof(path));

    if (NULL == strstr(path, valid_process_name.c_str()))
        return false;

    return true;
}



DWORD CProcessManage::StartProgram(std::string strProgram)
{
	DWORD dwPid = 0;

	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 

	ZeroMemory( &si, sizeof(si) ); 
	si.cb = sizeof(si); 
	ZeroMemory( &pi, sizeof(pi) ); 
	//si.wShowWindow = SW_HIDE;
	//si.dwFlags   =   STARTF_USESHOWWINDOW;   

	// Start the child process. 
	if( CreateProcess( NULL, // No module name (use command line). 
		(LPSTR)strProgram.c_str(), // Command line. 
		NULL,            // Process handle not inheritable. 
		NULL,            // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,            // Use parent's environment block. 
		NULL,            // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure. 
		&pi )            // Pointer to PROCESS_INFORMATION structure. 
		) 
	{ 
		return pi.dwProcessId;
	} 

	return dwPid;
}

bool CProcessManage::ExitProgram(DWORD pid)
{
    bool bRet = false;

    HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE, pid);   
    if(hProcess!=NULL)   
    {   
        TerminateProcess(hProcess,0);   
        CloseHandle(hProcess);
        bRet = true;
    }
    return bRet;
}