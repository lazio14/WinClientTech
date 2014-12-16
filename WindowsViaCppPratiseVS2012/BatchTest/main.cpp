#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
using namespace std;

volatile LONG g_nCurrentRunningTaskSum = 0;
volatile LONG g_nWorkIdx = 0;
PTP_WORK g_pWorkItem = NULL;

void NTAPI TaskHandler(PTP_CALLBACK_INSTANCE instance, PVOID Context, PTP_WORK Work)
{
	InterlockedIncrement(&g_nCurrentRunningTaskSum);
	InterlockedIncrement(&g_nWorkIdx);
	TCHAR szMsg[100] = {0};
	StringCchPrintf(szMsg, _countof(szMsg), TEXT("[%u]Task %u is starting"),  GetCurrentThreadId(), g_nWorkIdx);
	wcout << szMsg << endl;
	Sleep(5000);
	StringCchPrintf(szMsg, _countof(szMsg), TEXT("[%u]Task %u is done"),  GetCurrentThreadId(), g_nWorkIdx);
	wcout << szMsg << endl;
	if (InterlockedDecrement(&g_nCurrentRunningTaskSum))
	{
		wcout << "all is done" << endl;
	}
}

void main()
{
	g_pWorkItem = CreateThreadpoolWork(TaskHandler, NULL, NULL);
	SubmitThreadpoolWork((g_pWorkItem));
	SubmitThreadpoolWork((g_pWorkItem));
	SubmitThreadpoolWork((g_pWorkItem));
	SubmitThreadpoolWork((g_pWorkItem));
	system("pause");
	CloseThreadpoolWork(g_pWorkItem);
}