#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	// Ԥ����62k����������ҳ���СӦ����4k 8k 16k,�ú�����Ԥ��64k������Ҫ��֤������С��CPU page��С����������
	PVOID addr1 = VirtualAlloc((PVOID)(40 * 1024 * 1024 + 2 * 1024), 62 * 1024, MEM_RESERVE, PAGE_READWRITE);
	// ��һ��������Ϊ64k������ʱ��ϵͳ�Ὣ������ȡ64k����������addr2Ϊ50 * 1024 * 1024
	PVOID addr2 = VirtualAlloc((PVOID)(50 * 1024 * 1024 + 2 * 1024), 6 * 1024, MEM_RESERVE, PAGE_READWRITE);
	PVOID addr3 = VirtualAlloc(NULL, 6 * 1024, MEM_RESERVE | MEM_TOP_DOWN, PAGE_READWRITE);
// 	int* pInt = (int*)addr3; ֻ��Ԥ����û�е�������洢������Υ����ʡ�
// 	cout << *pInt << endl;
	VirtualAlloc(addr3, 6 * 1024, MEM_COMMIT, PAGE_READWRITE);
	int* pInt = (int*)addr3; // ����������洢���󣬿��Է��ʡ�
	cout << *pInt << endl;

	// ͬʱԤ���͵�������洢��
	PVOID addr4 = VirtualAlloc(NULL, 6 * 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	

	size_t page = GetLargePageMinimum();

}