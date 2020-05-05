#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string a = "hello world";
	cout << boost::algorithm::replace_first_copy(a, 'l', "m") << endl;
	cout << boost::algorithm::replace_nth_copy(a, 'l', 1, "m") << endl;
	cout << boost::algorithm::replace_last_copy(a, 'l', "m") << endl;
	cout << boost::algorithm::replace_all_copy(a, 'l', "m") << endl;
	cout << boost::algorithm::replace_head_copy(a, 5, "hate") << endl;
	cout << boost::algorithm::replace_tail_copy(a, 5, "hehhe") << endl;
	
	return 0;
} 
