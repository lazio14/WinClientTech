#include <windows.h>

DWORD WINAPI ChildThread(LPVOID pvParam);

DWORD WINAPI ParentThread(LPVOID pvParam)
{
	HANDLE hSeuProcessHandle = GetCurrentProcess(); //伪句柄，不会使引用计数增加。用来标志当前进程或者当前线程。
	HANDLE hSeuThreadHandle = GetCurrentThread();
	HANDLE hThreadParent;
	DuplicateHandle(GetCurrentProcess(),  // 引用计数会增加。 用DuplicateHandle可以把伪句柄转成真正的句柄。
					GetCurrentThread(),
					GetCurrentProcess(),
					&hThreadParent,
					0,
					FALSE,
					DUPLICATE_SAME_ACCESS);
	CreateThread(NULL, 0, ChildThread, (LPVOID)hThreadParent, 0, NULL);
	return 0;
}

DWORD WINAPI ChildThread(LPVOID pvParam)
{
	HANDLE hThreadParent = (HANDLE)pvParam;
	FILETIME ftCreationTime, ftExitTime, ftKernelTime, ftUserTime;
	GetThreadTimes(hThreadParent, &ftCreationTime, &ftExitTime, &ftKernelTime, &ftUserTime);
	CloseHandle(hThreadParent);
	return 0;
}

int main()
{
	CreateThread(NULL, 0, ParentThread, NULL, 0, NULL);
	system("pause");
	return 0;
}