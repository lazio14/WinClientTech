#include <windows.h>
#include <stdio.h>
#include <tchar.h>
int main()
{
	SetLastError(4);
	DWORD dw = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	printf(_T("%s"), lpMsgBuf);
	::LocalFree(lpMsgBuf);

	return 0;
}