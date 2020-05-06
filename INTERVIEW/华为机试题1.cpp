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

	cin >> m >> c >> n;  // ��ʾ����  n��ʾ����֮������Щֵ
	
	if (m <= 0 || n <= 0)
		return -1;

	vector<string> lines;
	string t;

	// ���뵱ǰ��
	for (int i=0; i<m; i++)
	{
		cin >> t;
		lines.push_back(t);
	}

	// �Ե�ǰ�н��н�ȡ �����
	for (int i = 0; i<m; i++)
	{
		t = lines[i]; // �õ���ǰ�е��ַ���
		
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

