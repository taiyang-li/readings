#include <boost/tokenizer.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ", "+", boost::keep_empty_tokens);
	string s = "boost c++ library"; 
	tokenizer tok(s, sep);
	for_each(tok.begin(), tok.end(), cout << boost::lambda::_1 << "\n");
	return 0;
}
