#include <windows.h>
#include <iostream>
using namespace std;

VOID APIENTRY TimerAPCRoutine(PVOID pvArgToComletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	cout << "APC" << endl;
}

void main()
{
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	LARGE_INTEGER li = {0};
	SetWaitableTimer(hTimer, &li, 1000, TimerAPCRoutine, NULL, FALSE);
	while (TRUE)
	{
		SleepEx(INFINITE, TRUE); // ¿ÉÌáÐÑ×´Ì¬¡£
	}
	CloseHandle(hTimer);
	system("pause");
}