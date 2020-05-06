#include <iostream>
using namespace std;

template <class T>
class my_auto_ptr
{
	public:
		explicit my_auto_ptr(T* ptr = 0) : _ptr(ptr) {}
		my_auto_ptr(my_auto_ptr<T>& rhs) : _ptr(rhs.release()) {}
		~my_auto_ptr() {
			cout << *_ptr << endl;
			delete _ptr;
		}

		// ����=
		my_auto_ptr<T>& operator =(my_auto_ptr<T>& rhs)
		{
			if (rhs._ptr != _ptr)
			{
				reset(rhs.release());
			}
			return *this;
		}

		// ����*
		T& operator *()
		{
			return *_ptr;
		}

		// ����->
		T* operator ->()
		{
			return _ptr;
		}

		// get����
		T* get() const
		{
			return _ptr;
		}
		
		// release����
		T* release()
		{
			T* old_ptr = _ptr;
			_ptr = NULL;
			return old_ptr;
		}

		// reset����
		void reset(T *p = 0)
		{
			if (_ptr!= p)
			{
				delete _ptr;
				_ptr = p;
			}
		}
	private:
		T* _ptr;
};

int main()
{	
	my_auto_ptr<double> rhs(new double(3.1415));
	double *p = new double(2.7815);

	// test * 
	cout << *rhs << endl;
	*rhs = 1.67;
	cout << *rhs << endl;

	// test get
	cout << *(rhs.get())  << endl;

	// test reset 
	rhs.reset(p);
	cout << *rhs << endl;

	return 0;
}

