#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

template<typename T> void counts();
template<typename T> void report(T &);



template <typename T>
class HasFriend
{
public:
	T item;
	static int ct;
public: 
	HasFriend(const T &i) : item(i) {ct++;}
	~HasFriend() {ct--;}
	friend void counts<T>();                      // 针对所有类型
	friend void report<>(const HasFriend<T> &); // 针对特定类型
};


template <typename T> 
int  HasFriend<T>::ct = 0;


template<typename T>
void counts()
{
	cout << "template size: " << sizeof(HasFriend<T>) << endl;
	cout << "HasFriend<double> counts: " << HasFriend<T>::ct << endl;
}

template<typename T>
void report(T &hf)
{
	cout << "HasFriend<int> item: " << hf.item << endl;
}

int main()
{
	counts<int>();
	HasFriend<int> hfi1(10);
	HasFriend<int> hfi2(20);
	HasFriend<double> hfdb(10.5);
	report(hfi1);
	report(hfi2);
	report(hfdb);
	counts<int>();
	counts<double>();
	
	return 0;
}
