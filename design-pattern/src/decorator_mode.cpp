#include <iostream>
#include <string>
using namespace std;

class Phone 
{
	public:
		Phone() {}
		virtual ~Phone() {}
		virtual void show_decorate() {}
};

class iPhone : public Phone
{
	public:
		iPhone(const string& name) : _name(name) {}	
		virtual ~iPhone() {}

		virtual void show_decorate()
		{
			cout << _name << "的装饰" << endl;
		}
	private:
		string _name;
};

class NokiaPhone : public Phone
{
	public:
		NokiaPhone(const string& name) : _name(name) {}
		virtual ~NokiaPhone() {}

		virtual void show_decorate()
		{
			cout << _name << "的装饰" << endl;
		}
	private:
		string _name;
};

class DecoratorPhone : public Phone
{
	protected:
		Phone* _phone;
	public:
		DecoratorPhone(Phone* phone) : _phone(phone) {}
		virtual void show_decorate()
		{
			if (_phone)
			{
				_phone->show_decorate();
			}
			add_decorate();
		}

		virtual void add_decorate() {}
};

class DecoratorPhoneA : public DecoratorPhone
{
	public:
		DecoratorPhoneA(Phone* phone) : DecoratorPhone(phone) {}
		
		virtual void add_decorate()
		{
			cout << "增加挂件" << endl;
		}

		/*
		virtual void show_decorate()
		{
			DecoratorPhone::show_decorate();
			add_decorate();
		}
		*/
};

class DecoratorPhoneB : public DecoratorPhone
{
	public:
		DecoratorPhoneB(Phone* phone) : DecoratorPhone(phone) {}

		virtual void add_decorate()
		{
			cout << "屏幕贴膜" << endl;
		}

		/*
		virtual void show_decorate()
		{
			DecoratorPhone::show_decorate();
			add_decorate();
		}
		*/
};


int main()
{
	Phone* iphone = new NokiaPhone("6300");	
	Phone* dpa = new DecoratorPhoneA(iphone);
	Phone* dpb = new DecoratorPhoneB(dpa);
	dpb->show_decorate();
	delete dpa;
	delete dpb;
	delete iphone;

	return 0;
}
