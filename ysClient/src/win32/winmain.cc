
#ifdef __OS_WIN__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#include <windows.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef int (CALLBACK* LPFNPIDGINMAIN)(HINSTANCE, int, char**);
typedef void (CALLBACK* LPFNSETDLLDIRECTORY)(LPCTSTR);
typedef BOOL (CALLBACK* LPFNATTACHCONSOLE)(DWORD);
static LPFNPIDGINMAIN pidgin_main = NULL;

static const char *get_win32_error_message(DWORD err) {
	static char err_msg[512];

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &err_msg, sizeof(err_msg), NULL);

	return err_msg;
}

int _stdcall
WinMain (struct HINSTANCE__ *hInstance, struct HINSTANCE__ *hPrevInstance,
		 char *lpszCmdLine, int nCmdShow)
{
	 char errbuf[512];
	 char pidgin_dir[MAX_PATH];
	 char exe_name[MAX_PATH];
	 HMODULE hmod;
	 char *tmp;
	 int ys_argc = __argc;
	 char **ys_argv = __argv;
	 int i;

	 /* Now we are ready for Pidgin .. */
	 if ((hmod = LoadLibrary("pidgin.dll")))
		 pidgin_main = (LPFNPIDGINMAIN) GetProcAddress(hmod, "pidgin_main");

	 if (!pidgin_main) {
		 DWORD dw = GetLastError();
		 BOOL mod_not_found = (dw == ERROR_MOD_NOT_FOUND || dw == ERROR_DLL_NOT_FOUND);
		 const char *err_msg = get_win32_error_message(dw);

		 _snprintf(errbuf, 512, "Error loading pidgin.dll.\nError: (%u) %s%s%s",
			 (UINT) dw, err_msg,
			 mod_not_found ? "\n" : "",
			 mod_not_found ? "This probably means that GTK+ can't be found." : "");
		 printf("%s\n", errbuf);
		 MessageBox(NULL, errbuf, TEXT("Error"), MB_OK | MB_TOPMOST);

		 return 0;
	 }

	 return pidgin_main(hInstance, ys_argc, ys_argv);
}

#endif // __OS_WIN__
