#include <iostream>
#include <list>
#include <string>
using namespace std;

class Observer
{
	public:
		Observer() {}
		virtual ~Observer() {}
		virtual void update() {}
};

class Blog 
{
	public:
		list<Observer*> _observer_list;
		string _status;

	public:
		Blog() {}
		virtual ~Blog() {}

		void attach(Observer* observer)
		{
			_observer_list.push_back(observer);
		}

		void remove(Observer* observer)
		{
			_observer_list.remove(observer);
		}

		void inotify()
		{
			for (list<Observer*>::iterator it = _observer_list.begin(); it != _observer_list.end(); it++)
				(*it)->update();
		}

		virtual void set_status(const string& status)
		{
			_status = status;
		}

		virtual string get_status() 
		{
			return _status;
		}
};

class BlogCSDN : public Blog
{
	private:
		string _name;

	public:
		BlogCSDN(const string& name) : _name(name) {}
		virtual ~BlogCSDN() {}

		virtual void set_status(const string& status)
		{
			_status = _name + ": " + status;
		}
};

class ObserverBlog : public Observer
{
	private:
		Blog* _blog;
		string _name;
		
	public:
		ObserverBlog(Blog* blog, const string& name) : _blog(blog), _name(name) {}
		virtual ~ObserverBlog() {}

		virtual void update()
		{
			cout << _name << " get notice: " << _blog->get_status();
		}
};

int main()
{
	BlogCSDN* blog = new BlogCSDN("dandanla");	
	Observer* observer = new ObserverBlog(blog, "liyang");
	blog->attach(observer);

	// ÉèÖÃ×´Ì¬
	blog->set_status("finish the blog: how do i met your mother");
	blog->inotify();

	return 0;
	
}
