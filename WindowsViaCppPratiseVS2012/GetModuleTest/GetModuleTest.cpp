// GetModuleTest.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GetModuleTest.h"

extern "C" const IMAGE_DOS_HEADER __ImageBase;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	HMODULE hModule = GetModuleHandle(NULL);
	_tprintf(TEXT("0x%x\r\n"), hModule);

	_tprintf(TEXT("__ImageBase:0x%x\r\n"), (HINSTANCE)&__ImageBase);

	hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)_tWinMain, &hModule);

	_tprintf(TEXT("0x%x\r\n"), hModule);

	system("pause");
	return (int) 1;
}
