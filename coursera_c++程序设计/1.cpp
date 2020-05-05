#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;


class Student
{
	public:
		Student() {}
		~Student() {}

		void init()
		{	
			string line;
			cin >> line;
			replace(line.begin(), line.end(), ',', ' ');
			
			istringstream iss(line);
			iss >> _name >> _age >> _id >> _scoreYear1 >> _scoreYear2 >> _scoreYear3 >> _scoreYear4;

			/*
			cout << _name << endl;
			cout << _age << endl;
			cout << _id << endl;
			cout << _scoreYear1 << endl;
			cout << _scoreYear2 << endl;
			cout << _scoreYear3 << endl;
			cout << _scoreYear4 << endl;
			*/
		}

		void output()
		{
			cout << _name << "," << _age << "," << _id << "," << (_scoreYear1+_scoreYear2+_scoreYear3+_scoreYear4)/4 << endl;
		}
			
	private:
		string _name;
		int _age;
		string _id;
		int _scoreYear1;
		int _scoreYear2;
		int _scoreYear3;
		int _scoreYear4;
};

int main()
{
	Student stu;
	stu.init();
	stu.output();
	
	return 0;
}
