#include <boost/algorithm/string.hpp> 
#include <string>
#include <iostream> 
#include <vector>

using namespace std;

int main() 
{ 
	string s = "--algorithm--";
	cout << boost::algorithm::trim_left_copy_if(s, boost::algorithm::is_any_of("-")) << "." << endl;
	cout << boost::algorithm::trim_right_copy_if(s, boost::algorithm::is_any_of("-")) << "." << endl;
	cout << boost::algorithm::trim_copy_if(s, boost::algorithm::is_any_of("-")) << "." << endl;
	return 0;
} 
