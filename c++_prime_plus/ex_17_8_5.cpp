#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream> 
#include <cstring>
#include <cstdio>
#include <set> 

using namespace std;  	

void my_print(ostream &os, string &s);

int main() 
{
	set<string> names;

	// open file mat.dat 
	ifstream fin1("mat.dat");
	if (!fin1.is_open())
	{
		cout << "file mat.dat open failure" << endl;
		return -1;
	}

	// open file pat.dat 
	ifstream fin2("pat.dat");
	if (!fin2.is_open())
	{
		cout << "file pat.dat open failure" << endl;
		return -1;
	}

	// open file pat.dat 
	ofstream fout("matnpat.dat");
	if (!fout.is_open())
	{
		cout << "file matnpat.dat open failure" << endl;
		return -1;
	}
	
	string name;
	while(fin1 >> name)
		names.insert(name);
	while(fin2 >> name)  
		names.insert(name);

	for (auto it=names.begin(); it!=names.end(); it++) // 可用transform 或者 for_each 实现 
		fout << *it << endl;
	
	fin1.close();
	fin2.close();
	fout.close();

	system("pause");
	return 0;
}



void my_print(ostream &os, string &s)   
{
	os << s << endl; 
}




