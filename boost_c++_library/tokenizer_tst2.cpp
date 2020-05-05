#include <boost/tokenizer.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	string s = "boost c++ library"; 
	tokenizer tok(s, sep);
	for_each(tok.begin(), tok.end(), cout << boost::lambda::_2 << "\n");
	return 0;
}
