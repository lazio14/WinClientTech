#include <windows.h>

void main()
{
	HANDLE hFile = ::CreateFile(TEXT("tmp.txt"), 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_ALWAYS, 
		FILE_FLAG_DELETE_ON_CLOSE| FILE_ATTRIBUTE_TEMPORARY, 
		NULL);
	const int BUFSIZE = 4096;
	char chBuffer[BUFSIZE];         
	memcpy(chBuffer,"Test",4);
	DWORD dwWritenSize = 0;
	BOOL bRet = ::WriteFile(hFile, chBuffer, 4, &dw
		WritenSize, NULL);

	system("pause");
	memset(chBuffer, 0, sizeof(chBuffer));
	//���ļ����ȡ���ݡ�
	LONG lDistance = 0;
	DWORD dwPtr = SetFilePointer(hFile, lDistance, NULL, FILE_BEGIN);
	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		DWORD dwError = GetLastError() ;           
	}

	DWORD dwReadSize = 0;
	bRet = ::ReadFile(hFile,chBuffer,4,&dwReadSize,NULL); // ��ʱ�鿴���̣��ļ���С����0k������readfile�ܶ������ݡ�

	system("pause");
	CloseHandle(hFile); // �رվ����tmp.txt��ɾ����
}