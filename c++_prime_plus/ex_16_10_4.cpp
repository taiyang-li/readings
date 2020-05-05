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

int reduce(vector<long> &ar);

int main()
{
	long ar0[8] = {10, 20, 30, 30, 20, 10, 40, 50}; 
	
	vector<long> ar(ar0, ar0+8);
	reduce(ar);
	
	system("pause");
	return 0;
}
	

int reduce(vector<long> &ar)
{
	if (ar.empty())
		return 0;
	sort(ar.begin(), ar.end());
	auto it = unique(ar.begin(), ar.end());
	ar.resize(distance(ar.begin(), it));
	return ar.size();	
}



