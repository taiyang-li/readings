#include <iostream>
using namespace std;

int main()
{
	float rate = 0.0;
	float salary = 0.0;

	while(cin >> salary >> rate)
	{
		float property = salary;
		float price = 200.0;
		int year=1;

		while (year <= 20)
		{
			if (property >= price)
			{
				cout << year << endl;
				break;
			}
			property += salary;
			price *= (1+rate/100);
			year++;
		}
		if (year > 20)
			cout << "Impossible" << endl;
	}
	return 0;
}
