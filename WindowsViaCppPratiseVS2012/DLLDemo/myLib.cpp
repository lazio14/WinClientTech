#include <windows.h>

#define MYLIBAPI extern "C" __declspec(dllexport)

#include "MyLib.h"

int g_nResult;

int Add(int nLeft, int nRight)
{
	g_nResult = nLeft + nRight;
	return (g_nResult);
}

DWORD WINAPI ChildThread(LPVOID pvParam)
{	
	OutputDebugString(TEXT("================myLIB ChildThread================"));
	return 0;
}

BOOL WINAPI DllMain( HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved )
{
	HANDLE hThread;
	DWORD dwThreadId;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(TEXT("================DLL_PROCESS_ATTACH================"));
		OutputDebugString(TEXT("================may be dead lock================"));
		// 进程创建线程时，Dll会收到DLL_THREAD_ATTACH消息
		hThread = CreateThread(NULL, 0, ChildThread, NULL, 0, NULL);
// 		WaitForSingleObject(hThread, INFINITE);
 		OutputDebugString(TEXT("================not dead lock================"));
// 		CloseHandle(hThread);
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugString(TEXT("================DLL_PROCESS_DETACH================"));
		break;
	case DLL_THREAD_ATTACH:
		OutputDebugString(TEXT("================DLL_THREAD_ATTACH================"));
		break;
	case DLL_THREAD_DETACH:
		OutputDebugString(TEXT("================DLL_THREAD_DETACH================"));
		break;
	default:
		break;
	}
	return TRUE;
}