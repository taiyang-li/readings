#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Stock
{
private:
	string company;
	long shares;
	double share_val;
	double total_val;
	inline void set_tol() {
		total_val = shares * share_val;
	}
public:
	Stock(const string &co, long n, double pr);
	Stock() 
	{
		company = "no name";
		shares = 0;
		share_val = 0.0;
		total_val = 0.0;
	}
	~Stock()
	{
		cout << "bye , " << company << endl;
	}

	// this的用法
	const Stock & Stock::topval(const Stock &s) const 
	{
		if (s.total_val > total_val)
			return s;
		else
			return *this;
	}
	
	void acquire(const string &co, long n, double pr);
	void buy(long num, double price);       
	void sell(long num, double price);
	void update(double price);
	void show() const;
}; 

Stock::Stock(const string &co, long n, double pr)
{
	company = co;
	if (n<0)
	{
		std::cerr << "number of shares can't be negative" 
			       << company << "shares set to 0" << endl;
	}
	else
	{
		shares = n;
		share_val = pr;
		set_tol();
	}
}


void Stock::acquire(const string &co, long n, double pr)
{
	company = co;
	if (n<0)
	{
		cout << "number of share can not be negative" << company << "shares set to 0.n" ;
		shares = 0;
	}
	else
	{
		shares = n;
	}
	share_val = pr;
	set_tol();
}


void Stock::buy(long num, double price)
{
	if (num < 0)
		cout << "number of shares purchased cannot be negative" 
		      << "transaction is aborted" << endl;
	else
	{
		shares += num;
		share_val = price;
		set_tol();
	}
}


void Stock::sell(long num, double price)
{
	if (num < 0)
		cout << "number of shares sold can't be negative" 
			<< "transaction aborted" << endl;
	else if (num > shares)
		cout << "you can't sell more than you have!" 
		      << "transaction aborted" << endl;
	else
	{
		shares -= num;
		share_val = price;
		set_tol();
	}
}


void Stock::update(double price)
{
	share_val = price;
	set_tol();
}

void Stock::show() const 
{
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(3);
	cout << company << endl;
	cout << shares << "*" << share_val << "=" << total_val << endl;
}


const int STKS = 4;
int main()
{
	Stock fluffy_the_cat;

	// 使用stock接口函数
	fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
	fluffy_the_cat.show();

	fluffy_the_cat.buy(15, 18.125);
	fluffy_the_cat.show();

	fluffy_the_cat.sell(400, 20.00);
	fluffy_the_cat.show();

	fluffy_the_cat.buy(300000, 40.125);
	fluffy_the_cat.show();

	fluffy_the_cat.sell(300000, 0.125);
	fluffy_the_cat.show();
	
	// 使用stock构造函数
	Stock hehe = Stock("haha", 2, 2.0);
	
	// 使用const成员函数
	const Stock land = Stock("Kludgeshorn properties", 18, 0.5);
	land.show();


	// 使用对象数组
	Stock stocks[STKS] = {
		Stock("h1", 12, 20.0),
		Stock("h2", 200, 2.0),
		Stock("h3", 130, 3.25),
		Stock("h4", 60, 6.5)
	};
	
	cout << "stock holdings" << endl;
	int st;
	for (st = 0; st < STKS; st++)
		stocks[st].show();


	const Stock *top = &stocks[0];
	for (st=1; st < STKS; st++)
		top = &top->topval(stocks[st]);
	cout << "most valuable holding" << endl;
	top->show();

	system("pause");
	return 0;
}






