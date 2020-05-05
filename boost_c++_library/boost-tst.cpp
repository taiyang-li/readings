#include <boost/serialization/singleton.hpp>

using namespace std;
using namespace boost::serialization;

class A : public singleton<A> 
{
	public:
		A() : _n(10) {}
		~A() {}

		void set_value(int m)
		{
			_n = m;
		}

		int get_value()
		{
			return _n;
		}

	private:
		int _n;
}

int main()
{
	A.get_mutable_instance().set_value(10);
	cout << A.get_mutable_instance().get_value() << endl;
	return 0;
	
}
