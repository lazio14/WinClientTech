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

	BYTE buf[MAX_PATH] = {0};
	OVERLAPPED o = {0};
	o.Offset = 2;

	BOOL bReadDone = ReadFile(hFile, buf, MAX_PATH - 1, NULL, &o);
	DWORD dwError = GetLastError();

	// call some func that may be take large time.

	if (!bReadDone && dwError == ERROR_IO_PENDING)
	{
		WaitForSingleObject(hFile, INFINITE);
		bReadDone = TRUE;
	}

	if (bReadDone)
	{
		char result[MAX_PATH] = {0};
		memcpy(result, buf, o.InternalHigh); // o.InternalHigh 表示读入的长度
		result[o.InternalHigh] = '\0';
		cout << "success" << endl;
		cout << result << endl;
	}
	else
	{
		cout << "fail" << endl;
	}
}