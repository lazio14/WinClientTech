#include <windows.h>
using namespace std;

void main()
{
	// ����� FILE_SHARE_DELETE ���ļ�����ôDeleteFile����ֱ��ɾ���ļ���ֱ��CloseHandle���������ɾ����
	// ���򣬵���DeleteFile��ֱ��ɾ���ļ���

	HANDLE hFile = ::CreateFile(TEXT("deletefile.txt"), 0, FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DeleteFile(TEXT("deletefile.txt"));
		system("pause");
		CloseHandle(hFile);
	}
}