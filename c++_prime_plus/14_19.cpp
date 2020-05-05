#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

template <class T1, class T2>
class Pair
{
private:
	T1 a;
	T2 b;
public:
	T1& first() {return a;} 
	T2& second()  {return b;}
	T1 first() const {return a;}
	T2 second() const {return b;}
	Pair(const T1 &aval, const T2 &bval): a(aval), b(bval) {}
	Pair() {}
};

int main()
{
	Pair<string, int> ratings[4] = 
	{
		Pair<string, int>("the purpled duck" ,5),
		Pair<string, int>("jaque's prisco al fresco", 4),
		Pair<string, int>("cafe souffle", 5),
		Pair<string, int>("bertie's rats", 3)
	};

	int joints = sizeof(ratings)/ sizeof(Pair<string, int>);
	cout << "rating: \t eatery" << endl;
	for (int i=0; i<joints; i++)
	{
		cout << ratings[i].second() << "\t" << ratings[i].first() << endl;
	}
	
	ratings[3].first() = "liyang";
	ratings[3].second() = 10;
	cout << ratings[3].second() << "\t" << ratings[3].first() << endl;
	return 0;
}


