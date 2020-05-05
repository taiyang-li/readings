#include <iostream>
#include <string>
#include <fstream>

using namespace std;  	

int main(int argc, char *argv[])  
{
	if (argc < 2)
		cout << "usage: ./a.out <filename>"<< endl;
	ofstream fout1(argv[1]);  
	
	// 方法1  逐个字符复制  
	char ch;
	while(cin.get(ch) && ch != '#')  
		fout1.put(ch);
	fout1.close();  
	
	// 方法2：逐行复制 getline
	ofstream fout2(argv[1]);  
	string line;
	while(getline(cin, line) && line != "quit")
		fout2 << line << endl;
	fout2.close();
	 
	
	system("pause");
	return 0;
}




