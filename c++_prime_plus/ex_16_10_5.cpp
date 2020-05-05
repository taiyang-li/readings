// hangman.cpp -- some string methods
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

template <class T>
int reduce(vector<T> &ar);

int main()
{
	string ar0[4] = {"abc", "bv", "abc", "bc"};
	vector<string> ar(ar0, ar0+4);
	reduce(ar);
	
	system("pause");
	return 0;
}
	
template <class T>
int reduce(vector<T> &ar)
{
	if (ar.empty())
		return 0;
	
	sort(ar.begin(), ar.end());
	auto it = unique(ar.begin(), ar.end());
	ar.resize(distance(ar.begin(), it));  
	return ar.size();	
}



