#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/*
int getFromLine(const string& line, int& n, int& m)
{	
	if (line.empty())	
	{
		return -1;
	}

	size_t found = line.find(" ");
	if (found == string::npos)
	{
		return -1;
	}
	
	n = atoi(line.substr(0, found).c_str());
	int i = found;
	for (; i<line.size(); i++)
	{
		if (line[i] == ' ')
		{
			break;
		}
	}
	
	if (i == line.size())
	{
		return -1;
	}
	
	m = atoi(line.substr(i).c_str());
	return 0;
}
*/

class Monkey
{
public:
	Monkey()
	{
		_status = 1;
		_id = 1;
	}
	
	Monkey(int id)
	{
		_status = 1;
		_id = id;
	}

	~Monkey() {}

	void setId(int id)
	{
		_id = id;
	}
	
	int getId() const
	{
		return _id;
	}

	void quit()
	{
		_status = 0;
	}

	bool isQuit()
	{
		return _status == 0;
	}
		
private:
	int _status;
	int _id;
};


class MonkeyCircle
{

public:	
	MonkeyCircle(int n, int m) 
	{
		_quitNum = m;
		_totalMonkey = n;
		_leftMonkey = n;
		_monkeys = new Monkey[n];
		for (int i=0; i<n; i++)
		{
			_monkeys[i].setId(i+1);
		}	
	}

	~MonkeyCircle()
	{
		delete[] _monkeys;
	}

	int run()
	{
		int count=0;
		while(_leftMonkey)
		{
			for(int i=0; i<_totalMonkey; i++)
			{
				if (_monkeys[i].isQuit())
				{
					continue;
				}

				if (++count == _quitNum)
				{
					_monkeys[i].quit();		
					_leftMonkey--;
					// showMonkeys();
					if (_leftMonkey == 1)
					{
						return 0;
					}
					count = 0;
				}
			}
		}
		return -1;
	}
	
	int getKing()
	{
		for (int i=0; i<_totalMonkey; i++)
		{
			if (_monkeys[i].isQuit())
				continue;
			return _monkeys[i].getId();
		}
		return -1;
	}
	
	void showMonkeys()
	{
		for (int i=0; i<_totalMonkey; i++)
		{
			cout << i+1 << ":" << _monkeys[i].isQuit() << " ";
		}
		cout << endl;
	}
	
private:
	Monkey* _monkeys;
	int _leftMonkey;
	int _totalMonkey;
	int _quitNum;
};

int main()
{
	int n;
	int m;
	vector<int> results;
	
	string line;
	while (getline(cin, line))
	{
		int n = 0;
		int m = 0;
		istringstream iss(line);
		iss >> n >> m;
	
		line.clear();
		
		if (m <= 0 && n <= 0)
			break;

		MonkeyCircle mc(n, m);
		mc.run();
		results.push_back(mc.getKing());
	}

	for(vector<int>::iterator it = results.begin(); it != results.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}
