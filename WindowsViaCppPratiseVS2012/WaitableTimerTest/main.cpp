#include <windows.h>
#include <iostream>
using namespace std;

HANDLE g_hEvent;

void main()
{
	g_hEvent = CreateWaitableTimer(NULL, FALSE, NULL);
	// 调用结束后的2秒开始触发，每秒触发一次。
	const int nTimerUnitPerSecond = 10000000;
	LARGE_INTEGER li;
	li.QuadPart = - (2 * nTimerUnitPerSecond);
	SetWaitableTimer(g_hEvent, &li, 1000, NULL, NULL, FALSE); 

	int i = 0;
	while (TRUE)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		cout << i++ << endl;
		if (i == 5)
		{
			CancelWaitableTimer(g_hEvent);
			break;
		}
	}
}