#include <iostream>
#include <string>
#include <list>
using namespace std;

class Company
{
	public:
		Company(const string& name) : _name(name) {}
		virtual ~Company() {}
		virtual void show(int depth) {}
		virtual void add(Company* c) {}
	protected:
		string _name;
};

class ConcreteCompany : public Company
{
	public:
		ConcreteCompany(const string& name) : Company(name)
		{
			
		}

		~ConcreteCompany()
		{
		}

		void show(int depth)
		{
			for (int i=0; i<depth; i++)
				cout << "-";

			list<Company*>::iterator it = _company_list.begin();
			for (; it != _company_list.end(); it++)
			{
				(*it)->show(depth+2);
			}
		}

		void add(Company* company)	
		{
			_company_list.push_back(company);
		}


	private:
		list<Company* > _company_list;
};

class FinanceDepartment : public Company
{
	public:
		FinanceDepartment(const string& name) : Company(name) {}
		~FinanceDepartment() {}

		void show(int depth)
		{
			for (int i=0; i<depth; i++)
				cout << "-";

			cout << _name << endl;
		}
};

class HRDepartment : public Company
{
	public:
		HRDepartment(const string& name) : Company(name) {}
		~HRDepartment() {}

		void show(int depth)
		{
			for (int i=0; i<depth; i++)
				cout << "-";

			cout << _name << endl;
		}
};

int main()
{
	Company* root = new ConcreteCompany("�ܹ�˾");
	Company* leaf1 = new FinanceDepartment("����");
	Company* leaf2 = new HRDepartment("������Դ��");
	root->add(leaf1);
	root->add(leaf2);

	// �ֹ�˾A
	Company* mid1 = new ConcreteCompany("�ֹ�˾A");
	Company* leaf4 = new FinanceDepartment("����");
	Company* leaf5 = new HRDepartment("������Դ��");
	mid1->add(leaf4);
	mid1->add(leaf5);
	root->add(mid1);

	// �ֹ�˾B
	Company* mid2 = new ConcreteCompany("�ֹ�˾B");
	Company* leaf6 = new FinanceDepartment("����");
	Company* leaf7 = new HRDepartment("������Դ��");
	mid2->add(leaf6);
	mid2->add(leaf7);
	root->add(mid2);

	root->show(0);

	return 0;
}
