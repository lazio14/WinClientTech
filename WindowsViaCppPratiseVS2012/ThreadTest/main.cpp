#include <windows.h>

DWORD WINAPI ChildThread(LPVOID pvParam);

DWORD WINAPI ParentThread(LPVOID pvParam)
{
	HANDLE hSeuProcessHandle = GetCurrentProcess(); //α���������ʹ���ü������ӡ�������־��ǰ���̻��ߵ�ǰ�̡߳�
	HANDLE hSeuThreadHandle = GetCurrentThread();
	HANDLE hThreadParent;
	DuplicateHandle(GetCurrentProcess(),  // ���ü��������ӡ� ��DuplicateHandle���԰�α���ת�������ľ����
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