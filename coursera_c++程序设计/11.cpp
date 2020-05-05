// 加减乘除四则运算 
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define BIG_SIZE 100
class Big 
{
	public:
		Big()
		{
			memset(_arr, 0, sizeof(int)*BIG_SIZE);	
			_dig = 0;
			_flag = 0;
		}
		
		Big(const string& s)
		{
			memset(_arr, 0, sizeof(int)*BIG_SIZE);	
			_dig = s.size();
			_flag = 0;
			fromString(s);	
		}
		
		void updateDig()
		{
			int i;
			for (i=BIG_SIZE-1; i>=0; i--)
			{
				if (_arr[i] != 0)
					break;
			}
			_dig = i+1;
		}

		void fromString(const string& s)
		{
			// 去掉前面的零
			char* str = new char[s.length()+1];
			strcpy(str, s.c_str());

			// 读数字
			int i = _dig - 1;
			int j = 0;
			for (; i>=0 && j<_dig; i--, j++)
			{
				_arr[i] = *(str+j) - '0'; 
			}
			delete[] str;
		}

		string toString() const 
		{
			string ret;
			if (_flag)
				ret += "-";

			int i = _dig-1;
			for (; i>=0; i--)
			{
				char tmp = _arr[i] + '0';
				ret += tmp;
			}
			return ret;
		}

		friend void split(const Big& src, Big& msb, Big& lsb, int n)
		{
			msb._dig = n;
			lsb._dig = src._dig - n;

			for (int i=0; i<n; i++)
			{
				msb._arr[i] = src._arr[src._dig-n+i];
			}

			for (int i=0; i<lsb._dig; i++)
			{
				lsb._arr[i] = src._arr[i];
			}
		}

		friend Big join(const Big& msb, const Big& lsb)
		{
			Big ret;
			ret._dig = msb._dig + lsb._dig;
			for (int i=0; i<lsb._dig; i++)
			{
				ret._arr[i] = lsb._arr[i];
			}
			for (int i=lsb._dig; i<ret._dig; i++)
			{
				ret._arr[i] = msb._arr[i-lsb._dig];
			}
			return ret;
		}
		
		Big operator<<(int n)
		{
			Big ret;
			ret._flag = 0;
			ret._dig = _dig + n;
			for (int i=0; i<_dig; i++)
			{
				ret._arr[i+n] = _arr[i];
			}
			return ret;
		}

		Big operator>>(int n)
		{
			Big ret;
			ret._flag = 0;
			ret._dig = _dig + n;
			for (int i=0; i<ret._dig; i++)
			{
				ret._arr[i] = _arr[i+n];
			}
			return ret;
		}
		
		friend bool operator<(const Big& a, const Big& b)
		{
			if (a._dig > b._dig)
				return false;
			else if (a._dig < b._dig)
				return true;
			else
				return a.toString() < b.toString();
		}

		friend bool operator>=(const Big& a, const Big& b )
		{
			return !(a<b);
		}

		friend bool operator>(const Big& a, const Big& b)
		{
			if (a._dig < b._dig)
				return false;
			else if (a._dig > b._dig)
				return true;
			else
				return a.toString() > b.toString();
		}

		friend bool operator<=(const Big& a, const Big& b)
		{
			return !(a>b);
		}

		friend Big operator+(const Big& a, const Big& b)
		{
			Big ret;
			int maxDig = max(a._dig, b._dig);
			ret._dig = maxDig; 
			int i = 0;
			int carry = 0;

			for (i=0; i<maxDig; i++)
			{
				int tmp = a._arr[i] + b._arr[i] + carry;	
				ret._arr[i] = tmp % 10;
				carry = tmp/10;
			}

			if (carry)
			{
				ret._arr[i] = carry;
				ret._dig++;
			}
			return ret;
		}

		friend Big operator-(const Big& a)
		{
			Big ret(a);
			ret._flag = 1 - a._flag;
			return ret;
		}

		friend Big operator-(const Big& a, const Big& b)
		{
			Big ret;
			if (a._dig < b._dig || 
				a._dig == b._dig && a.toString() < b.toString())
			{
				ret = b-a;
				ret._flag = 1;
				return ret;
			}

			int maxDig = max(a._dig, b._dig);
			int carry = 0;
			int i = 0;
			for (; i<maxDig; i++)
			{
				int tmp = a._arr[i] - b._arr[i] - carry;
				ret._arr[i] = tmp;
				if (tmp < 0)
				{
					ret._arr[i] += 10;
					carry = 1;
				}
			}
			ret.updateDig();
			return ret;
		}
		
		friend Big operator*(const Big& a, const Big& b)
		{
			Big ret;
			int len = a._dig;
			for (int i=0; i<len; i++)
			{
				Big tmpbig;
				tmpbig._dig = b._dig;
				int digit = a._arr[i];
				int carry = 0;
				for (int j=0; j<b._dig; j++)
				{
					int tmp = digit * b._arr[j] + carry;	
					tmpbig._arr[j] = tmp%10;
					carry = tmp/10;
				}
				if (carry)
				{
					tmpbig._arr[b._dig] = carry;
					tmpbig._dig++;
				}
				ret = ret + (tmpbig << i);
			}
			return ret;
		}

		friend Big operator/(const Big& a, const Big& b)
		{
			Big ret;		
			Big remainder;
			Big dividend(a);
			int pos = a._dig - 1;
			bool isFinish = false;
			
			while (pos >= 0)
			{
				Big msb;
				Big lsb;
				Big tmp;

				// 获取被除数
				for (int i=1; i<=dividend._dig; i++)
				{
					split(dividend, msb, lsb, i);
					tmp = join(remainder, msb); 
					if (tmp < b)
					{
						pos--;
						isFinish = pos < 0;
					}
					else
						break;
				}
				if (isFinish)
					break;

				// 获取相除结果
				int count = 0;
				while (tmp._flag != 1)
				{
					tmp = tmp - b; 
					count++;
				}
				count--;
				ret._arr[pos--] = count;

				// 更新数据 
				remainder = b-(-tmp);
				dividend = lsb;
			}
			ret.updateDig();
			return ret;
		}
			
	private:
		int _arr[BIG_SIZE];
		int _flag;
		int _dig;
};
// 大数的加减乘除 
int main()
{	
	string str_num1;
	string str_num2;
	char op;

	cin >> str_num1 >> op >> str_num2;

	Big num1(str_num1); 
	Big num2(str_num2);
	Big ret;
	
	switch(op)
	{
		case '+':
			ret = num1 + num2;
			break;
		case '-':
			ret = num1 - num2;
			break;
		case '*':
			ret = num1 * num2;
			break;
		case '/':
			ret = num1 / num2;
			break;
		default:
			cerr << "wrong input" << endl;
	}
	cout << ret.toString() << endl;

	/*
	Big num("1234");
	Big ret1;
	Big ret2;
	split(num, ret1, ret2, 2);
	cout << "ret1: " << ret1.toString() << endl;
	cout << "ret2: " << ret2.toString() << endl;
	num = join(ret1, ret2);
	cout << "num: " << num.toString() << endl;
	*/ 

	return 0;
}



