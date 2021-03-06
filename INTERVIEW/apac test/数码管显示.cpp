// https://code.google.com/codejam/contest/3214486/dashboard#s=p1
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>
#include <set>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <exception>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>

using namespace std;

typedef  unsigned char  uchar;                       // 用一个8位二进制数的低7位表示数码管对应的数字编码

const string IN_FILE = "A-small-practice.in";        // 输入文件
const string OUT_FILE = "A-small-practice.out";       // 输出文件 

map<uchar, int> tb_code2num;                      
map<int, uchar> tb_num2code;

void tb_code2num_init();  // code2num 查找表的初始化
void tb_num2code_init();  // num2code 查找表的初始化

uchar find_next_code(vector<uchar> &code_list);       // 输入一组带broken segment的code, 输出下一个带broken segment的code
uchar dec_code(uchar cur_code);                       // 给定一个不带broken segment的code, 输出相邻的下一个不带broken segment的code
string code2string(uchar code);
uchar string2code(string str);

void print_code(int begin_num, int len);


int main()
{
	tb_code2num_init();
	tb_num2code_init();
	
	int case_num = 0;
	
	// 打开文件
	ifstream ifile(IN_FILE);
	ofstream ofile(OUT_FILE);

	
	// 读取测试样粒个数
	ifile >> case_num;
	
	// 遍历每一个测试用例
	for (int case_count = 1; case_count <= case_num && !ifile.eof(); ++case_count)
	{
		int len = 0;  // 当前测试样例的长度
		vector<uchar> code_list;
		ifile >> len;

		// 遍历测试样例的每一个code
		for (int i=0; i<len; i++)
		{
			string str_cur_code;
			ifile >> str_cur_code;
			code_list.push_back(string2code(str_cur_code));
		}
		
		// 进行处理
		cout << "---------------------------" << endl;
		cout << case_count << endl;
		uchar next_code = find_next_code(code_list);
		
		// 结果输出到文件中
		ofile << "Case #" << case_count << ": ";
		if (next_code == 0x80)
			ofile << "ERROR!" << endl;
		else
			ofile << code2string(next_code) << endl;
	}
	
	ifile.close();
	ofile.close();
	
	getchar();
	return 0;
}


void tb_code2num_init()
{
	tb_code2num[0x7e] = 0;   
	tb_code2num[0x30] = 1;
	tb_code2num[0x6d] = 2;
	tb_code2num[0x79] = 3;
	tb_code2num[0x33] = 4;
	tb_code2num[0x5b] = 5;
	tb_code2num[0x5f] = 6;
	tb_code2num[0x70] = 7;
	tb_code2num[0x7f] = 8;
	tb_code2num[0x7b] = 9;
}


void tb_num2code_init()
{
	tb_num2code[0] = 0x7e;  // 0xfe
	tb_num2code[1] = 0x30;  // 0x30
	tb_num2code[2] = 0x6d;  // 0x6d
	tb_num2code[3] = 0x79;  // 0x79
	tb_num2code[4] = 0x33;  // 0x33
	tb_num2code[5] = 0x5b;  // 0xb3  
	tb_num2code[6] = 0x5f;  // 0x5f
	tb_num2code[7] = 0x70;  // 0x70
	tb_num2code[8] = 0x7f;  // 0x7f
	tb_num2code[9] = 0x7b;  // 0x7b
}



uchar dec_code(uchar cur_code)
{	
	int cur_num = tb_code2num[cur_code];
	int next_num = (cur_num == 0) ? 9 : (cur_num-1);
	return tb_num2code[next_num];
}


string code2string(uchar code)
{
	string res;
	int pt = 6;
	
	while (pt>=0)
	{
		if (code & 1<<pt)
			res.push_back('1');
		else
			res.push_back('0');
		--pt;
	}
	return res;
}


uchar string2code(string str)
{
	uchar code = 0x00;
	for (int i=0; i<7; ++i)
	{
		if (str[i] == '1')
			code |= 1<<(6-i);
	}
	return code;	
}



void print_code(int begin_num, int len)
{
	int cur_num = 0;
	cout << endl;
	for (int i=0; i<len; i++)
	{	
		// cur_num 不断更新
		if (i == 0)
			cur_num = begin_num;
		else
			cur_num = (cur_num+10-1) % 10;
		
		// 打印数字
		cout << cur_num << ": ";
		
		// 打印数字对应的code
		cout << code2string(tb_num2code[cur_num]) << endl;
	}
}




// 函数:给出一组数 用于确认下一个数字
uchar find_next_code(vector<uchar> &code_list) 
{
	vector<uchar> next_code;  
	
	const int len = code_list.size();
	
	// 异常情况1
	if (len == 0)
		return 0x80;

	// 异常情况2
	if (len == 1)
	{
		if (code_list[0] == 0x7f)
			return 0x70;
		return 0x80;
	}

	
	for (int i=9; i>=0; i--)
	{
		uchar begin_code = tb_num2code[(uchar)i];     // 假设code list 中第一个数字为i
		uchar broken_segment = 0x00;     // 已经确定的broken segment
		
		// 按照之前的假设, 依次比较每一个元素
		int j = 0;
		uchar cur_code = 0x00;
		for (j=0; j<len; j++)
		{
			// 依据假设，得到 在没有borken segment的情况下的 code
			if (j == 0)
				cur_code = begin_code;
			else
				cur_code = dec_code(cur_code);
			
			
			if ((code_list[j] & cur_code) != code_list[j])
				break;
			else
			{ 
				// 确定broken segment不会亮 
				if ((code_list[j] & (~broken_segment)) != code_list[j])
					break;

				// 更新broken_segment
				broken_segment |= cur_code - code_list[j];
			}
		}
		
		
		if (j != len)
			continue;

		
		//在检查一遍，确保broken segment 不会再发光
		cur_code = begin_code;
		for (j=0; j<len; j++)
		{
			if ((cur_code & (~broken_segment)) != code_list[j])
				break;
			cur_code = dec_code(cur_code);
		}
		
		if (j != len)
			continue; 
		
		// 如果遍历过程中，所有cur_code都满足条件
		next_code.push_back(dec_code(cur_code) & (~broken_segment));
		
		print_code(i, len);
		
			
	}

	// 如果有唯一解
	if (next_code.size() == 1)
		return next_code[0];
	else
		return 0x80;
}
