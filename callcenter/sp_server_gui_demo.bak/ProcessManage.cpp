#include "stdafx.h"
#include "ProcessManage.h"
#include "TinyXmlHelper.hpp"

using namespace helper;

//////////////////////////////////////////////////////////////////////////
DWORD CProcessManage::IsProgramRunning(DWORD pid) 
{
	//HANDLE hProcess = HANDLE(pid);
	//DWORD dwExitCode;
	//if( GetExitCodeProcess(hProcess, &dwExitCode) )
	//	return (dwExitCode == STILL_ACTIVE) ? pid : 0;
	//return DWORD(-1);

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |  
		PROCESS_VM_READ,                                       
		FALSE, pid );                                  

	if (hProcess)                                              
	{                         
		return pid;
	}

	return 0;
}

DWORD CProcessManage::StartProgram(std::string strProgram)
{
	DWORD dwPid = 0;

	STARTUPINFO si; 
	PROCESS_INFORMATION pi; 

	ZeroMemory( &si, sizeof(si) ); 
	si.cb = sizeof(si); 
	ZeroMemory( &pi, sizeof(pi) ); 
	si.wShowWindow = SW_HIDE;
	si.dwFlags   =   STARTF_USESHOWWINDOW;   

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
		//do nothing
		//::MessageBox("CreateProcess failed.");
		//ErrorExit( "CreateProcess failed." ); 
	} 

	return dwPid;
}
