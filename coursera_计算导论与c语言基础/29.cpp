#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{	
	string line;
	getline(cin, line);
	
	size_t found = line.find('.');
	line = line.substr(0, found);
	
	string word;
	string longestWord;
	istringstream iss(line);
	while (iss >> word)
	{
		if (word.size() > longestWord.size())
		{
			longestWord = word;
		}
	}
	cout << longestWord << endl;

	return 0;
}
