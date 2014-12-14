#include <windows.h>
using namespace std;

void main()
{
	// 如果以 FILE_SHARE_DELETE 打开文件，那么DeleteFile不会直接删除文件。直到CloseHandle后才真正的删除。
	// 否则，调用DeleteFile能直接删除文件。

	HANDLE hFile = ::CreateFile(TEXT("deletefile.txt"), 0, FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DeleteFile(TEXT("deletefile.txt"));
		system("pause");
		CloseHandle(hFile);
	}
}