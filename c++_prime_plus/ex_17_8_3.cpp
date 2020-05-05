#include <iostream>
#include <string>
#include <fstream> 
#include <cstring>

using namespace std;  	

int main(int argc, char *argv[])  
{
	if (argc != 3)
		cout << "usage: ./a.out  <src_file> <dst_file> "<< endl;

	argv[1] = "1.txt";
	argv[2] = "2.txt";
	string src_file(argv[1]);
	string dst_file(argv[2]);
	
	ifstream fin;
	ofstream fout;
	
	fin.open(src_file);
	fout.open(dst_file);

	if (!fin.is_open())
		cout << "open src_file failed" << endl;
	if (!fout.is_open())
		cout << "open dst_file failed" << endl;

	string line;
	while(getline(fin, line))
	{
		fout << line;
		fout << endl;
	}	
	cout << "done" << endl;
	
	fin.close();
	fout.close();

 
	system("pause");
	return 0;
}




