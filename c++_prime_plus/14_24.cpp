#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;


template <typename T>
class ManyFriend
{
private:
	T item;
public:
	ManyFriend(const T &i) : item(i) {}
	template<typename C, typename D> friend void  show2(C &, D &);
};



template <typename C, typename D> 
void show2(C &c, D &d)
{
	cout << c.item << ", " << d.item << endl;
}

int main()
{
	ManyFriend<int> hfi1(10);
	ManyFriend<int> hfi2(20);
	ManyFriend<double> hfdb(10.5);
	cout << "hfi1, hfi2" << endl;
	show2(hfi1, hfi2);
	cout << "hfdb, hfi1" << endl;
	show2(hfdb, hfi1);
	cout << "done" << endl;
	return 0;
}
