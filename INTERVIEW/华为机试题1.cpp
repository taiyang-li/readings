#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


int main()
{
	int m;
	int n;
	char c;

	cin >> m >> c >> n;  // 表示行数  n表示排列之后有哪些值
	
	if (m <= 0 || n <= 0)
		return -1;

	vector<string> lines;
	string t;

	// 加入当前行
	for (int i=0; i<m; i++)
	{
		cin >> t;
		lines.push_back(t);
	}

	// 对当前行进行截取 并输出
	for (int i = 0; i<m; i++)
	{
		t = lines[i]; // 得到当前行的字符串
		
		int left_len = t.size();
		int len = left_len;
		while(left_len > 0)
		{
			if (left_len >= 8)
			{
				cout << t.substr(len-left_len, n) << endl;
				left_len -= 8;
			}
			else
			{
				cout << t.substr(len-left_len);
				string zeros(n-left_len, '0');
				cout << zeros << endl;
				left_len = 0;
			}
		}
	}
	getchar();
	getchar();
	return 0;
}

