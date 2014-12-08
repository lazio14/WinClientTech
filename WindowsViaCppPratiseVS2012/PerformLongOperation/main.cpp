#include <windows.h>
#include <iostream>
using namespace std;
__int64 FileTimeToQuadWord(PFILETIME pft)
{
	return (Int64ShllMod32(pft->dwHighDateTime, 32) | pft->dwLowDateTime);
}

void LongOperation()
{
	int i = 0;
	while (true)
	{
		i++;
		if (i == 100000000)
		{
			break;
		}
	}
}

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	FILETIME ftKernelTimeStart, ftKernelTimeEnd;
	FILETIME ftUserTimeStart, ftUserTimeEnd;
	FILETIME ftDummy;
	__int64 qwKernaelTimeElapsed, qwUserTimeElapsed, qwTotalTimeElapsed;

	GetThreadTimes(GetCurrentThread(), &ftDummy, &ftDummy, &ftKernelTimeStart, &ftUserTimeStart);
	LongOperation();
	GetThreadTimes(GetCurrentThread(), &ftDummy, &ftDummy, &ftKernelTimeEnd, &ftUserTimeEnd);
	qwKernaelTimeElapsed = FileTimeToQuadWord(&ftKernelTimeEnd) - FileTimeToQuadWord(&ftKernelTimeStart);
	qwUserTimeElapsed = FileTimeToQuadWord(&ftUserTimeEnd) - FileTimeToQuadWord(&ftUserTimeStart);
	qwTotalTimeElapsed = qwKernaelTimeElapsed + qwUserTimeElapsed;
	cout << "thread total time is:" << qwTotalTimeElapsed << endl;

	
	return 0;
}

void main()
{
	ULONGLONG qwStartTime = GetTickCount64();
	LongOperation();
	ULONGLONG qwElapsedTime = GetTickCount64() - qwStartTime;
	cout << "main thread total time is " << qwElapsedTime << endl;

	HANDLE hThread = CreateThread(NULL, 0, ChildThread, NULL, 0, NULL);
	CloseHandle(hThread);
	system("pause");
}