#include <iostream>
using namespace std;

// 抽象经理类
class Manager
{
	protected:
		Manager* _boss;
		string _name;

	public:
		Manager(Manager* boss, const string& name) : _boss(boss), _name(name) {}
		virtual void deal_with_request(const string& name, int num) {}
};

// 经理
class CommonManager : public Manager
{
	public:
	CommonManager(Manager* boss, const string& name) : Manager(boss, name) {}
	virtual void deal_with_request(const string& name, int num)
	{
		if (num <= 500 )  
		{
			cout << "CommonManager: " << _name << " approved " << "Worker: " << name << " increase " << num << endl;
		}
		else
		{
			cout << "CommonManager: " << _name << " can't handle it, up to boss" << endl;
			_boss->deal_with_request(name, num);
		}
	}
};

// 总监
class Majordomo : public Manager
{
	public: 
		Majordomo(Manager* boss, const string& name) : Manager(boss, name) {}
	virtual void deal_with_request(const string& name, int num)
	{
		if (num <= 1000 )  
		{
			cout << "Majordomo: " << _name << " approved " << "Worker: " << name << " increase " << num << endl;
		}
		else
		{
			cout << "Majordomo: " << _name << " can't handle it, up to boss: " << endl;
			_boss->deal_with_request(name, num);
		}
	}

};

// 总监
class GeneralManager : public Manager
{
	public:
	GeneralManager(Manager* boss, const string& name) : Manager(boss, name) {}
	virtual void deal_with_request(const string& name, int num)
	{
		cout << "GeneralManager: " << _name << " approved " << "Worker: " << name << " increase " << num << endl;
	}
};

int main()
{
	Manager* general = new GeneralManager(NULL, "A");
	Manager* majordomo = new Majordomo(general, "B");
	Manager* common = new CommonManager(majordomo, "C");

	common->deal_with_request("D", 200);
	common->deal_with_request("E", 600);
	common->deal_with_request("F", 1300);

	return 0;
}
