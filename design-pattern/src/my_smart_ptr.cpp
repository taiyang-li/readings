#include <iostream>
using namespace std;

template <class T>
class my_smart_ptr
{
	public:
		my_smart_ptr(T* ptr) : _ptr(ptr), _count(new size_t(1))  {}
		my_smart_ptr(const my_smart_ptr<T>& rhs) : _ptr(rhs._ptr), _count(rhs._count)
		{
			++(*_count);
		}

		~my_smart_ptr()
		{
			decrease_count();
		}

		// 重载=
		my_smart_ptr<T>& operator=(my_smart_ptr<T>& rhs) 
		{
			decrease_count();
			_ptr = rhs._ptr;
			_count = rhs._count;
			++(*_count);
			return *this;
		}

		// 重载*
		T& operator *()
		{
			return *_ptr;
		}

		// 重载->
		T* operator ->()
		{
			return _ptr;
		}
		
		// 函数get_ref_count
		size_t get_ref_count() const
		{
			return *_count;
		}
	private:
		T* _ptr;
		size_t* _count;

		void decrease_count()
		{
			--(*_count);
			if (*_count == 0)
			{
				delete _ptr;
				delete _count;
			}
		}
};

int main()
{
	my_smart_ptr<double> sp1(new double(1.1));
	
	// test *
	cout << *sp1 << endl;
	*sp1 = 2.2;
	cout << *sp1 << endl;

	// test get_ref_count
	cout << "count: " << sp1.get_ref_count() << endl;

	// test = 
	my_smart_ptr<double> sp2(new double(3.3));
	sp1 = sp2;
	cout << *sp1 << endl;
	cout << *sp2 << endl;
	cout << "count: " << sp1.get_ref_count() << endl;
	cout << "count: " << sp2.get_ref_count() << endl;

	return 0;
}
