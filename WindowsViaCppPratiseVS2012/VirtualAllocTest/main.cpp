#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	// 预定了62k的区域，由于页面大小应该是4k 8k 16k,该函数会预定64k的区域，要保证区域大大小是CPU page大小的整数倍。
	PVOID addr1 = VirtualAlloc((PVOID)(40 * 1024 * 1024 + 2 * 1024), 62 * 1024, MEM_RESERVE, PAGE_READWRITE);
	// 第一个参数不为64k整数倍时，系统会将它向下取64k的整数倍。addr2为50 * 1024 * 1024
	PVOID addr2 = VirtualAlloc((PVOID)(50 * 1024 * 1024 + 2 * 1024), 6 * 1024, MEM_RESERVE, PAGE_READWRITE);
	PVOID addr3 = VirtualAlloc(NULL, 6 * 1024, MEM_RESERVE | MEM_TOP_DOWN, PAGE_READWRITE);
// 	int* pInt = (int*)addr3; 只是预定，没有调拨物理存储器，会违规访问。
// 	cout << *pInt << endl;
	VirtualAlloc(addr3, 6 * 1024, MEM_COMMIT, PAGE_READWRITE);
	int* pInt = (int*)addr3; // 调拨了物理存储器后，可以访问。
	cout << *pInt << endl;

	// 同时预定和调拨物理存储器
	PVOID addr4 = VirtualAlloc(NULL, 6 * 1024, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	

	size_t page = GetLargePageMinimum();

}