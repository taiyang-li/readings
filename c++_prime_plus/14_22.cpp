#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;


template <typename T>
class HasFriend
{
private:
	T item;
	static int ct;
public: 
	HasFriend(const T &i) : item(i) {ct++;}
	~HasFriend() {ct--;}
	friend void counts();                      // 针对所有类型
	friend void reports(const HasFriend<T> &); // 针对特定类型
};


template <typename T> 
int  HasFriend<T>::ct = 0;


void counts()
{
	cout << "HasFriend<double> counts: " << HasFriend<int>::ct << endl;
	cout << "HasFriend<double> counts: " << HasFriend<double>::ct << endl;
}

void reports(const HasFriend<int> &hf)
{
	cout << "HasFriend<int> item: " << hf.item << endl;
}

void reports(const HasFriend<double> &hf)
{
	cout << "HasFriend<double> item: " << hf.item << endl;
}


int main()
{
	cout << "no objects declared " << endl;
	counts();

	HasFriend<int> hfi1(10);
	cout << "after hfi1 declared" << endl;
	counts();

	HasFriend<int> hfi2(20);
	cout << "after hfi1 declared" << endl;
	counts();
	
	
	HasFriend<double> hfdb(10.5);
	cout << "after hfi1 declared" << endl;
	counts();
	
	reports(hfi1);
	reports(hfi2);
	reports(hfdb);
	cout << "done" << endl;
	return 0;
}
