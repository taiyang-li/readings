#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <functional>  
#include <fstream> 
#include <vector>

using namespace std;  	


class Store
{
private:
	ofstream &os;  // 成员参数   
public:
	Store(ofstream &os_): os(os_) {}  
	void operator ()(const string &s) 
	{ 
		int len = s.size(); 
		os.write((char *)&len, sizeof(int));  // 先把长度写入   
		os.write(s.data(), len);             // 再写字符串
	}
}; 



void GetStrs(ifstream &is, vector<string> &vstr);

void ShowStr(const string &str);


int main() 
{
	vector<string> vostr;
	string temp;

	cout << "enter strings(empty line to quit)" << endl;
	while (getline(cin, temp) && !temp.empty())    
	{
		vostr.push_back(temp);  
	}
	cout << "here is your input: " << endl;  
	for_each(vostr.begin(), vostr.end(), ShowStr);
	
	ofstream fout("strings.dat",  ios_base::out | ios_base::binary);  
	for_each(vostr.begin(), vostr.end(), Store(fout)); 

	fout.close(); 
	
	vector<string> vistr;
	ifstream fin("strings.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
		cout << "open file strings.dat failed" << endl;
	
	GetStrs(fin, vistr);
	fin.close();
	
	cout << "here are the string read from the file" << endl;
	for_each(vistr.begin(), vistr.end(), ShowStr);
	
	
	system("pause");
	return 0;
}

void ShowStr(const string &str)
{
	cout << str << endl; 
}

void GetStrs(ifstream &is, vector<string> &vstr)
{
	vstr.clear();	
	int len;
	string str; 
	char cstr[100];
	while (is.read((char *)&len, sizeof(int)))    
	{
		cout << len << endl;  
		
		// 读取字符串
		is.read(cstr, len);
		cstr[len] = '\0'; 
		str = cstr;
		vstr.push_back(str); 
	}
}






