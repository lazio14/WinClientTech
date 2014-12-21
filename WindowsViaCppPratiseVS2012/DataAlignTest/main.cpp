#include <windows.h>
#include <iostream>
using namespace std;

void SomeFunc(PVOID pvDataBuffer)
{
	char c = * (PBYTE)pvDataBuffer;
	pvDataBuffer = (PVOID)((PBYTE)pvDataBuffer + 1);
	DWORD dw = * (DWORD *)pvDataBuffer;
}

void main()
{
	DWORD dw = 0X12344344;
	DWORD *pdw = &dw;
	SomeFunc(&dw);
}

