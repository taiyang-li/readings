#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void file_it(ostream &os, double fo, const double fe[], int n);

const int LIMIT = 5;


int main()
{
	ofstream fout;
	const char *fn = "ep-data.txt";
	fout.open(fn);
	if (!fout.is_open())
	{
		cout << "canot open " << fn << ", Bye" << endl;
		exit(EXIT_FAILURE);
	}
	double objective;
	double eps[LIMIT];
	cout << "enter the focal length of your telescope objective in mm: ";
	cin >> objective;
	cout << "enter the focal length, in mm, of " << LIMIT << " eyepieces " << endl;
	for (int i=0; i<LIMIT; i++)
	{
		cout << "eyepiece #" << i+1 << ": ";
		cin >> eps[i];
	}
	file_it(fout, objective, eps, LIMIT);
	file_it(cout, objective, eps, LIMIT);
	cout << "Done" << endl;
	system("pause");
	return 0;
	
}

void file_it(ostream &os, double fo, const double fe[], int n)  
{
	ios_base::fmtflags initial;

	initial = os.setf(ios_base::fixed);   // 设置定长显示格式
	os.precision(10);
	os << "focal length of objective" << fo << endl;

	os.setf(ios::showpoint);
	os.precision(1);
	os.width(12);
	os << "f.1, eyepiece";
	

	os.width(15);
	os << "magnification" << endl;
	for (int i=0; i<n; i++)
	{
		os.width(12);
		os << fe[i];
		os.width(15);
		os << int(fo/fe[i]+0.5) << endl;
	}
	os.setf(initial);
}




