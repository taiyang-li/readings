#include <iostream> 
#include <iterator> 
#include <set> 
using namespace std;
int main() { 
	int a[] = {8,7,8,9,6,2,1}; 
	// �ڴ˴�������Ĵ���
	set<int> v(a, a+sizeof(a)/sizeof(int));
	ostream_iterator<int> o(cout," ");
	copy( v.begin(),v.end(),o); 
	return 0;
}
