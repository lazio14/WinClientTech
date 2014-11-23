#include <windows.h>
#include <stdio.h>
#include <tchar.h>
int main()
{
	int a = ::CompareString(GetThreadLocale(), NORM_IGNORECASE, TEXT("abcde"), 3, TEXT("abc"), 3);
	int b = ::CompareString(GetThreadLocale(), NORM_IGNORECASE, TEXT("abc"), 3, TEXT("abc"), 3);
	int c = ::CompareString(GetThreadLocale(), NORM_IGNORECASE, TEXT("abcde"), 5, TEXT("abc"), 3);
	
	return 0;
}