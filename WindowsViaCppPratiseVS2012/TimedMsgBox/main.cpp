#include <tchar.h>
#include <strsafe.h>
#include <windows.h>
#include <iostream>
using namespace std;
TCHAR g_szCaption[100];
unsigned g_nSecLeft = 0;

#define ID_MSGBOX_STATIC_TEXT 0x0000ffff

VOID CALLBACK MsgBoxTimeoutCallback(
	PTP_CALLBACK_INSTANCE pInstance,
	PVOID pvContext,
	PTP_TIMER pTimer
	)
{
	HWND hwnd = FindWindow(NULL, g_szCaption);
	if (hwnd != NULL)
	{
		if (g_nSecLeft == 1)
		{
			EndDialog(hwnd, IDOK);
			return;
		}
		TCHAR szMsg[100] = {0};
		InterlockedExchangeAdd(&g_nSecLeft, -1);
		StringCchPrintf(szMsg, _countof(szMsg), TEXT("You have %u seconds to respond"), g_nSecLeft);
		SetDlgItemText(hwnd, ID_MSGBOX_STATIC_TEXT, szMsg);
	}
	else
	{
		cout << "can't find window" << endl;
	}
}

int main()
{
	_tcscpy_s(g_szCaption, 100, TEXT("Timed Message Box"));
	g_nSecLeft = 10;

	PTP_TIMER lpTimer = CreateThreadpoolTimer(MsgBoxTimeoutCallback, NULL, NULL);
	if (lpTimer == NULL)
	{
		TCHAR szMsg[MAX_PATH] = {0};
		StringCchPrintf(szMsg, _countof(szMsg), TEXT("IMPOSSIBLE TO CREATE THE TIMER:%u"), GetLastError());
		MessageBox(NULL, szMsg, TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return -1;
	}

	ULARGE_INTEGER ulRelativeStartTime;
	ulRelativeStartTime.QuadPart = (LONGLONG)-(10000000);
	FILETIME ftRelativeStartTime;
	ftRelativeStartTime.dwHighDateTime = ulRelativeStartTime.HighPart;
	ftRelativeStartTime.dwLowDateTime = ulRelativeStartTime.LowPart;

	SetThreadpoolTimer(lpTimer, &ftRelativeStartTime, 1000, 0);

	MessageBox(NULL, TEXT("You have 10 seconds to respond"), g_szCaption, MB_OK);
	CloseThreadpoolTimer(lpTimer);

	MessageBox(NULL, (g_nSecLeft == 1 ? TEXT("Timeout") : TEXT("User responded")), TEXT("result"), MB_OK);

	return 0;
}