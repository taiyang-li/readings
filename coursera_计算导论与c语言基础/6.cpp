#include <iostream>
using namespace std;

int main()
{
	int n, x, y;
	cin >> n >> x >> y;
	
	cout << n - int(ceil(float(y)/x)) << endl;
	return 0;
}
