#include <iostream>
#include <string>
#include <fstream> 
#include <cstring>
#include <cstdio>


using namespace std;  	

int main() 
{
	string src_file1("1.txt");
	string src_file2("2.txt");
	string dst_file("3.txt");

	ifstream fin1(src_file1);
	ifstream fin2(src_file2);
	ofstream fout(dst_file);
	
	if (!(fin1.is_open() && fin2.is_open() && fout.is_open()))
	{
		cout << "open file failed" << endl;
		return -1;
	}
	
	string line1, line2;
	string line;
	while (!fin1.eof() || !fin2.eof())
	{
		line.clear();
		if (getline(fin1, line1))
		{
			line += line1;
			line += " ";
		}
		if (getline(fin2, line2))
			line += line2;

		fout << line << endl;
	}
	
	fin1.close();
	fin2.close();
	fout.close();

 
	system("pause");
	return 0;
}




