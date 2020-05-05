#include <string>
#include <iostream>

using namespace std;


class AcctABC
{
private:
	string fullName;
	long acctNum;
	double balance;
	
protected:
	struct Formatting
	{
		ios_base::fmtflags flag;
		streamsize pr;
	};
	const string &FullName() const {return fullName;}
	long AcctNum() const {return acctNum;}
	Formatting  SetFormat() const;
	void Restore(Formatting &f) const;

public:
	AcctABC(const string &s = "NullBody", long an = -1, double bal = 0.0);
	void Deposit(double amt);
	virtual void Withdraw(double amt) = 0;
	double Balance() const {return balance;}
	virtual void ViewAcct() const = 0;
	virtual ~AcctABC() {}
};



class Brass : public AcctABC
{	
public:
	Brass(const string &s = "NullBody", long an = -1, double bal = 0.0)
		: AcctABC(s, an, bal) {}
	virtual void Withdraw(double amt);
	virtual void ViewAcct() const;
	virtual ~Brass() {}
};


class BrassPlus : public AcctABC
{
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const string &s = "NullBody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
	BrassPlus(const Brass &ba, double ml = 500, double r = 0.1);
	virtual void ViewAcct() const;
	virtual void Withdraw(double amt);
	void ResetMax(double m) {maxLoan = m;}
	void ResetRate(double r) {rate = r;}
	void ResetOwes() {owesBank = 0;}
	
};


AcctABC::AcctABC(const string &s, long an, double bal)
{	
	fullName = s;
	acctNum = an;
	balance = bal;
}


void AcctABC::Deposit(double amt)
{
	if (amt < 0)
		cout << "negative deposit not allowed" <<
			 ", deposit is cancelled" << endl;
	else
		balance += amt;
}

void AcctABC::Withdraw(double amt)
{
	balance -= amt;
}


AcctABC::Formatting AcctABC::SetFormat() const
{
	Formatting f;
	f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
	f.pr = cout.precision(2);
	return f;
}

void AcctABC::Restore(Formatting &f) const
{
	cout.setf(f.flag, ios_base::floatfield);
	cout.precision(f.pr);
}


// Brass methods
void Brass::Withdraw(double amt)
{
	if (amt < 0)
		cout << "withdraw amount must be positive, "
			<< "withdraw is cancelled" << endl;
	else if (amt <= Balance())
		AcctABC::Withdraw(amt);
	else
		cout << "withdraw exceeds balance, "
			<< "withdraw is cancelled" << endl;
}

void Brass::ViewAcct() const 
{
	Formatting f = SetFormat();
	cout << "Brass client: " << FullName() << endl;
	cout << "Account Number: " << AcctNum() << endl;
	cout << "Balance: $" << Balance() << endl;
	Restore(f);
}





// BrassPlus method

BrassPlus::BrassPlus(const string &s, long an, double bal, double ml, double r) : AcctABC(s, an, bal)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}


BrassPlus::BrassPlus(const Brass &ba, double ml, double r)
	: AcctABC(ba)
{
	maxLoan = ml;
	owesBank = 0.0;
	rate = r;
}

void BrassPlus::ViewAcct() const 
{
	Formatting f = SetFormat();
	
	cout << "Brass client: " << FullName() << endl;
	cout << "Account Number: " << AcctNum() << endl;
	cout << "Balance: $" << Balance() << endl;
	cout << "maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%" << endl;
	
	Restore(f);
}

void BrassPlus::Withdraw(double amt)
{
	Formatting f = SetFormat();
	
	double bal = Balance();
	
	if (amt <= bal)
		AcctABC::Withdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)
	{
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;
		Deposit(advance);
		AcctABC::Withdraw(amt);
	}
	else
		cout << "credit limit exceeded." << endl;
	Restore(f);
}


const int CLIENTS = 4;
int main()
{
	AcctABC *p_clients[CLIENTS];
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
