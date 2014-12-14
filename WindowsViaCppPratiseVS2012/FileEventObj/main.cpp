#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	HANDLE hFile = ::CreateFile(TEXT("fin.txt"), 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_ALWAYS, 
		FILE_FLAG_OVERLAPPED, 
		NULL);

	HANDLE hEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	BYTE buf1[MAX_PATH] = {0};
	OVERLAPPED o1 = {0};
	o1.Offset = 2;
	o1.hEvent = hEvent1;
	ReadFile(hFile, buf1, MAX_PATH - 1, NULL, &o1);

	HANDLE hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	BYTE buf2[MAX_PATH] = {0};
	OVERLAPPED o2 = {0};
	o2.Offset = 0;
	o2.hEvent = hEvent2;
	ReadFile(hFile, buf2, MAX_PATH - 1, NULL, &o2);

	HANDLE h[2];
	h[0] = o1.hEvent;
	h[1] = o2.hEvent;
	DWORD dw = WaitForMultipleObjects(2, h, FALSE, INFINITE);
	switch (dw - WAIT_OBJECT_0)
	{
	case 0:
		{
			char result[MAX_PATH] = {0};
			memcpy(result, buf1, o1.InternalHigh); // o.InternalHigh 表示读入的长度
			result[o1.InternalHigh] = '\0';
			cout << "success 1" << endl 
				<< result << endl;
		}
		break;
	case 1:
		{
			char result[MAX_PATH] = {0};
			memcpy(result, buf2, o2.InternalHigh); // o.InternalHigh 表示读入的长度
			result[o2.InternalHigh] = '\0';
			cout << "success 2" << result << endl
				<< result << endl;
		}
		break;
	default:
		break;
	}
	system("pause")
;}