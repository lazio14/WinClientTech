#include <iostream>
using namespace std;

int funcenstein()
{
	int retVal = 5;
	__try
	{
		return retVal;
	}
	__finally
	{
		retVal = 10;
	}

	return 15;
}

void main()
{
	cout << funcenstein() << endl;
	system("pause");
}