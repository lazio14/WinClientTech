#include <iostream>
using namespace std;
int main()
{
	int i = 0;
	while (1)
	{
		i++;
		cout << i << endl;
		if (i % 100 == 0)
		{
			i = 0;
		}
	}
	return 0;
}