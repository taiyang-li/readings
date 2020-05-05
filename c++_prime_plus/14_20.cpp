#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

template <class T>
class Beta
{
private:
	// a template class
	template <class V>
	class hold
	{
	private:
		V val;
	public:
		hold(V v=0) : val(v) {}
		void show() const {cout << val << endl;}
		V Value() const {return val;}
	};
	hold<T> q;
	hold<int> n;
public:
	Beta(T t, int i): q(t), n(i) {}
	template <class U>
	U balb(U u, T t) {
		return (q.Value() + n.Value()) * u /t;
	}
	void Show() const {q.show(); n.show();}

};



int main()
{	
	Beta<double> guy(3.5, 3);
	cout << "T was set to double" << endl;
	guy.Show();
	cout << "V == T, and T == double, then V == double" << endl;
	cout << guy.balb(10, 2.3) << endl;
	cout << "U == int" << endl;
	cout << guy.balb(10.0, 2.3) << endl;
	cout << "U == double" << endl;
	cout << "Done" << endl;
	return 0;
}
