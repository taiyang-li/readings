#include <iostream> 
#include <vector> 

using namespace std;

void print(int i)
{
	std::cout << i << std::endl;
}

int main() 
{ 
	int a[4] = {1, 2, 3, 4};		
	vector<int> b(a, a+4);
	for_each(b.begin(), b.end(), print);
	return 0;
} 
