#include <iostream>
using namespace std;

int funcenstein()
{
	int retVal = 5;
	__try
	{
		goto ReturnVal;
	}
	__finally
	{
		retVal = 10;
	}

ReturnVal:
	return retVal;
}

void main()
{
	cout << funcenstein() << endl;
	system("pause");
}