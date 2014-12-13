#include <windows.h>
#include <concrt.h>
#include <iostream>
using namespace std;

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	while (TRUE)
	{
		cout << 1 << endl;
	}
	return 0;
}

void main()
{
	HANDLE hThread = CreateThread(NULL, 0, ChildThread, NULL, 0, NULL);
	system("pause");
	SuspendThread(hThread);
	CONTEXT context;
	context.ContextFlags = CONTEXT_FULL;
	GetThreadContext(hThread, &context);

	context.Eip = 0x00010000;
	context.ContextFlags = CONTEXT_FULL;
	SetThreadContext(hThread, &context);
	ResumeThread(hThread);
	system("pause");
}