#include <windows.h>

void main()
{
	HANDLE hFile = ::CreateFile(TEXT("filesize.txt"), 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_ALWAYS, 
		0, 
		NULL);
	LARGE_INTEGER liFileSize;
	::GetFileSizeEx(hFile, &liFileSize);

	ULARGE_INTEGER ulFileSize;
	ulFileSize.LowPart = GetCompressedFileSize(TEXT("filesize.txt"), &ulFileSize.HighPart);
}