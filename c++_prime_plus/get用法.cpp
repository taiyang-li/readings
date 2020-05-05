#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{	
	// get(arr, arr_len)并不读取换行符，也就是说，换行符还在输入缓冲区当中
	// 在此种情况下，可用get()读取字符(换行符)
	
	const int ArrSize = 20;
	char name[ArrSize];
	char dessert[ArrSize];
	
	cout << "enter your name" << endl;
	cin.get(name, ArrSize).get();
	cout << "enter your favorite dessert" << endl;
	cin.get(dessert, ArrSize).get();
	cout << name << endl;
	cout << dessert << endl;
	system("pause");
	return 0;
}




