#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

typedef ios_base::fmtflags format;
typedef streamsize precis;          
const int CLIENTS = 4;

format setFormat();
void restore(format f, precis p);

class Brass
{
private:
	string fullName;         
	long accNum;
	double balance;
public:
	Brass(const string &s = "Nullbody", long an = -1, 
			double bal = 0.0);
	void Deposit(double amt);
	virtual void Withdraw(double amt);
	double Balance() const;
	virtual void ViewAcct() const;
	virtual  ~Brass() {}
};


Brass::Brass(const string &s, long an, double bal)
{
	fullName = s;
	accNum = an;
	balance = bal;
}

void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "negative deposit not allowed" 
			<< "deposit is cancelled" << endl;
	else
		balance += amt;
}

void Brass::Withdraw(double amt)
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	
	if (amt < 0)
		cout << "Withdrawal amount must be positive: "
			<< "Withdrawal canceled" << endl;
	else if (amt <= balance)
		balance -= amt;
	else
		cout << "Withdrawl amount of $" << amt 
			<< "exceeds your balance" << endl;
	restore(initialState, prec);
}


double Brass::Balance() const 
{
	return balance;
}


void Brass::ViewAcct() const 
{	
	format initialState = setFormat();
	precis prec = cout.precision(2);
	cout << "Client: " << fullName << endl;
	cout << "Account Number: " << accNum << endl;
	cout << "Balance: $" << balance << endl;
	restore(initialState, prec);
}




class BrassPlus : public Brass
{
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const string &s="Nullbody", long an = -1, 
			double bal = 0.0, double ml = 500,
			double r = 0.11125);
	BrassPlus(const Brass &ba, double ml = 500, 
			double r = 0.11125);
	
	virtual void ViewAcct() const;
	virtual void Withdraw(double amt);
	void ResetMax(double m) {maxLoan = m;}
	void ResetRate(double r) {rate = r;}
	void ResetOwes() {owesBank = 0;}
};

// Brass Plus methods 
BrassPlus::BrassPlus(const string &s, long an, double bal, 
		double ml, double r) : Brass(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass &ba, double ml, double  r):Brass(ba)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

void BrassPlus::ViewAcct() const 
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	Brass::ViewAcct();
	cout << "maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%" << endl;
	restore(initialState, prec);
}


void BrassPlus::Withdraw(double amt)
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	
	double bal = Balance();
	
	if (amt <= bal)
		Brass::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)
	{
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;
		Deposit(advance);
		Brass::Withdraw(amt);
	}
	else
		cout << "credit limit exceeded." << endl;
	restore(initialState, prec);
}

format setFormat()
{
	// set up format
	return cout.setf(ios_base::fixed, ios_base::floatfield);
}


void restore(format f, precis p)
{
	cout.setf(f, ios_base::floatfield);
	cout.precision(p);
}

int main()
{
	Brass *p_clients[CLIENTS];
	string temp;
	long tempnum;
	double tempbal;
	char kind;
	
	for (int i=0; i<CLIENTS; i++)
	{
		cout << "enter clients name: ";
		getline(cin,temp);
		cout << "enter clients account number: ";
		cin >> tempnum;
		cout << "enter opening balance: $";
		cin >> tempbal;
		cout << "enter 1 for Brass acount or " 
			<< "2 for BrassPlus account: ";
		while (cin >> kind && (kind != '1' && kind != '2'))
			cout << "enter either 1 or 2: ";
		if (kind == '1')
			p_clients[i] = new Brass(temp, tempnum, tempbal);
		else
		{
			double tmax, trate;
			cout << "enter the overdraft limit, $";
			cin >> tmax;
			cout << "enter the interest rate "
				<< "as a decimal fraction: ";
			cin >> trate;
			p_clients[i] = new BrassPlus(temp, tempnum, tempbal,
					tmax, trate);
		}
		while (cin.get() != '\n')
			continue;
	}
	cout << endl;
	for (int i=0; i<CLIENTS; i++)
	{
		p_clients[i]->ViewAcct();
		cout << endl;
	}

	for (int i=0; i<CLIENTS; i++)
	{
		delete p_clients[i];
	}

	cout << "Done" << endl;
	return 0;
}
