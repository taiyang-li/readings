#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string s = "123456789algorithm128638634";
	cout << boost::algorithm::trim_left_copy_if(s, boost::algorithm::is_digit()) << "." << endl;
	cout << boost::algorithm::trim_right_copy_if(s, boost::algorithm::is_digit()) << "." << endl;
	cout << boost::algorithm::trim_copy_if(s, boost::algorithm::is_digit()) << "." << endl;
	return 0;
} 
