#include <iostream>
#include <string>
#include <new>

using namespace std;

const int BUF = 512;


class JustTesting
{
private:
	string words;
	int number;
public:
	JustTesting(const string &s = "JustTesting", int n=0)
	{
		words = s;
		number = n;
		cout << words << " constructed" << endl;
	}
	
	~JustTesting() 
	{
		cout << words << " destroyed" << endl;
	}
	
	void Show() const {
		cout << words << ", " << number << endl;
	}
};


int main()
{
	char *buffer = new char[BUF];
	JustTesting *pc1, *pc2;
	
	pc1 = new (buffer) JustTesting;
	pc2 = new JustTesting("heap1", 20);
	
	cout << "memory block address: " << endl;
	cout << "buffer: " << (void *) buffer << "\theap: " << pc2 << endl;
	
	cout << "memory contents: " << endl;
	cout << pc1 << ": ";
	pc1->Show();
	cout << pc2 << ": ";
	pc2->Show();
	
	JustTesting *pc3, *pc4;
	//pc3 = new (buffer) JustTesting("Bad Idea", 6);
	pc3 = new (buffer+sizeof(JustTesting)) JustTesting("better idea", 6);
	pc4 = new JustTesting("Heap2", 10);

	cout << "memory contents" << endl;
	cout << pc3 << ": ";
	pc3->Show();
	cout << pc4 << ": ";
	pc4->Show();
	
	delete pc2;
	delete pc4; 
	pc3->~JustTesting();
	pc1->~JustTesting();
	delete []buffer;
	cout << "Done" << endl;
	return 0;

}


