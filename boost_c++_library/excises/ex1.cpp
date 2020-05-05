#include <iostream> 
#include <cstring> 
#include <boost/shared_array.hpp>

using boost::shared_array;

/*
char *get(const char *s) 
{ 
	int size = std::strlen(s); 
	char *text = new char[size + 1]; 
	std::strncpy(text, s, size + 1); 
	return text; 
} 
*/

shared_array<char> get(const char *s)
{
	int size = strlen(s);
	shared_array<char> text(new char[size+1]); 
	strncpy(text.get(), s, size+1);
	std::cout << text.get() << std::endl;
	return text;
}

/*
void print(char *text) 
{ 
	std::cout << text << std::endl; 
} 
*/

void print(shared_array<char> text)
{
	std::cout << text.get() << std::endl;
}

int main(int argc, char *argv[]) 
{ 
	if (argc < 2) 
	{ 
		std::cerr << argv[0] << " <data>" << std::endl; 
		return 1; 
	} 

	print(get(argv[1])); 
	return 0;
} 
