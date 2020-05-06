#include <iostream>
#include <string>
using namespace std;

class Point
{
	public:
		Point() : _x(0), _y(0) {}
		Point(int x, int y) : _x(x), _y(y) {}
		int x() const {return _x;}
		int y() const {return _y;}
		Point& x(int xv) {_x = xv; return *this;}
		Point& y(int yv) {_y = yv; return *this;}

	private:
		int _x;
		int _y;
};

class Handle
{
	public:
		Handle() : _point(new Point()), _count(new size_t(1)) {}
		Handle(int x, int y) : _point(new Point(x, y)), _count(new size_t(1)) {}
		Handle(const Point &p) : _point(new Point(p)), _count(new size_t(1)) {} 
		Handle(const Handle& h) : _count(h._count), _point(h._point) {++(*_count);}
		~Handle() {decr_count();}

		// operator = 
		Handle& operator=(const Handle& h)
		{
			++(*(h._count));
			decr_count();
			_count = h._count;
			_point = h._point;
			return *this;
		}

		int x() const 
		{
			return _point->x();
		}

		int y() const 
		{
			return _point->y();
		}

		// 指针语意 多个指针指向同一块内存区域
		Handle& x(int xv)
		{
			_point->x(xv);
			return *this;
		}
		Handle& y (int yv)
		{
			_point->y(yv);
			return *this;
		}

		void decr_count() 
		{
			--(*_count);
			if (*_count == 0)
			{
				delete _point;
			}
		}

	private: 
		size_t* _count;
		Point* _point;
};

int main()
{
	// test construct 1 
	Handle h1;		
	cout << h1.x() << ", " << h1.y() << endl;

	// test construct 2 
	Handle h2(10, 15);
	cout << h2.x() << ", " << h2.y() << endl;

	// test construct 3 
	Point p(2,3);
	Handle h3(p);
	cout << h3.x() << ", " << h3.y() << endl;

	// test construct 4
	Handle h4 = h3;
	cout << h4.x() << ", " << h4.y() << endl;

	return 0;
}
