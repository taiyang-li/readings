#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
	private:    
		double r,i;
	public:    
		void Print() {
			cout << r << "+" << i << "i" << endl;
		}

		// 在此处补充你的代码
		Complex& operator=(char* other)
		{
			int a, b;
			char tmp[100];
			
			char* p = other;

			// 复制a
			int pos = 0;
			while(*p != '+' && *p != '\0')
			{
				tmp[pos++] = *p;
				p++;
			}
			tmp[pos] = '\0';
			a = atoi(tmp);
			

			// 复制b
			p++;
			pos = 0;
			while (*p != '\0')
			{
				tmp[pos++] = *p;
				p++;
			}
			tmp[pos] = '\0';
			b = atoi(tmp);
			
			// sscanf(other,"%d+%di", &a, &b);	
			r = a;
			i = b;
			return *this;
		}
};

int main() {
	Complex a;
	a = "3+4i"; a.Print();
	a = "5+6i"; a.Print();
	return 0;
}
