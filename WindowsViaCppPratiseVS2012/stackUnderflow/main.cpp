#include <windows.h>
void main()
{
	BYTE aBytes[0x10];
	//aBytes[10000] = 1; // �ᱨ��
	MEMORY_BASIC_INFORMATION mbi;
	SIZE_T size = VirtualQuery(aBytes, &mbi, sizeof(mbi));

	SIZE_T s = (SIZE_T)mbi.AllocationBase + 1024 * 1024;
	PBYTE pAddr = (PBYTE)s;
	BYTE* pBytes = (BYTE*)VirtualAlloc(pAddr, 0x10000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	aBytes[0x10000] = 1; // ���ᱨ����Ϊ����պ����߳�ջ�ĺ��������һ���ڴ档
}