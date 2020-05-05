#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <map>
#include <exception>
#include <iomanip>
using namespace std;

const string weapons[3] = {"sword", "bomb", "array"};

class QuarterException : public exception
{
	public:
		QuarterException(const string& msg) throw()
		{
			_msg = msg;
		}

		~QuarterException() throw() {}

		const char* what() throw() 
		{
			string s;
			s += "QuartreException: ";
			s += _msg;
			s += "\n";
			return s.c_str();
		}

	private:
		string _msg;
};

class Warrior
{
	public:
		Warrior()
		{
			_type = "unknown";
			_id = 0;
			_life = 0;
			_strength = 0;
		}

		Warrior(const string& type, int id, int life, int strength)
		{
			_type = type;
			_id = id;
			_life = life;
			_strength = strength;
		}

		~Warrior() {}
		
		string get_type() const 
		{
			return _type;
		}

		int get_id() const 
		{
			return _id;
		}

		int get_life() const 
		{
			return _life;
		}
		
		int get_strength() const 
		{
			return _strength;
		}

		Warrior& operator=(const Warrior& w)
		{
			this->_type = w._type;
			this->_id = w._id;
			this->_life = w._life;
			this->_strength = w._strength;
			return *this;
		}
	private:
		int _id;
		int _life;
		int _strength;
		string _type;
};

class Quarter
{
	public:
		Quarter() {}
		~Quarter() {}
		
		void set_order(const vector<string>& order)
		{
			_order = order;
		}

		void set_order(const char* order[], int len)
		{
			for(int i=0; i<len; i++)
			{
				string s(order[i]);
				_order.push_back(s);
			}
		}

		void set_cost(const string& warrior, int cost)
		{
			_warrior_cost[warrior] = cost;	
		}
		
		void set_cost(const char* warriors[], int* cost, int len)
		{
			for (int i=0; i<len; i++)
			{
				_warrior_cost[string(warriors[i])] = cost[i];
			}
		}
		
		void set_name(const string& name)
		{
			_name = name;
		}
		
		string get_name() const 
		{
			return _name;
		}
		
		void set_life(int life)
		{
			_life = life;
		}
		
		int get_life() const
		{
			return _life;
		}	

		int get_count(const string& warrior)
		{
			return _warrior_count[warrior];
		}
		
		bool isStopped() const 
		{
			return _isStopped;
		}

		bool isFirstStoped() const
		{
			return _isFirstStopped;
		}
		
		bool next()
		{
			if (_order.empty())
			{
				throw QuarterException("order queue is empty");
			}

			int i = 0; 
			int len = _order.size();
			do 
			{
				_curr = (_curr+1)%len;
				i++;
			}  while (_life < _warrior_cost[_order[_curr]] && i < len);

			if (len == i)
			{
				if (!_isStopped)
				{
					_isFirstStopped = true;
					_isStopped = true;
					return true;
				}
				else
				{
					_isFirstStopped = false;
					return false;
				}
			}
			_life -= _warrior_cost[_order[_curr]];
			_warrior_count[_order[_curr]]++;
			_last_id++;
			
			string type = _order[_curr];
			int life = _warrior_cost[_order[_curr]];
			_warriors.push_back(Warrior(type, _last_id, life, life));
			return true;
		}

		void reset()
		{
			_curr = -1;
			_last_id = 0;

			_warrior_count.clear();
			_warrior_cost.clear();
			_warriors.clear();

			_isStopped = false;
			_isFirstStopped = false;
		}

		void showProcess(int time)
		{
			if (!_isStopped)
			{
				showProcess1(time);
			}
			else if (_isFirstStopped)
			{
				showProcess2(time);
			}
		}
			
		void showProcess1(int time)
		{
			char buf[100];

			if (_curr < 0)
				throw QuarterException("index out of range");
			string warrior_type = _order[_curr];
			int warrior_id = _last_id;
			int warrior_life = _warrior_cost[warrior_type];

			snprintf(buf, 100, "%03d", time);
			cout << buf << " ";
			cout << _name << " ";
			cout << warrior_type << " ";
			cout << warrior_id  << " ";
			cout << "born with strength " << warrior_life << ",";
			cout << _warrior_count[warrior_type] << " " << warrior_type << " in " << _name << " headquarter";
			cout << endl;

			// 输出第二行 每种武士的特点，如武器，忠诚或者道德
			if (warrior_type == "iceman")
			{
				cout << "It has a " << weapons[warrior_id%3] << endl;
			}
			else if (warrior_type == "lion")
			{
				cout << "It's loyalty is " << _life << endl; 
			}
			else if (warrior_type == "dragon")
			{
				cout << "It has a " << weapons[warrior_id%3] <<  ",and it's morale is " ;
				cout << setprecision(2) << fixed << float(_life)/_warrior_cost["dragon"] << endl;
			}
			else if (warrior_type == "ninja")
			{
				cout << "It has a " << weapons[warrior_id%3] << " and a " << weapons[warrior_id%3+1] << endl;
			}

		}

		void showProcess2(int time)
		{
			char buf[100];
			snprintf(buf, 100, "%03d", time);
			cout << buf << " " << _name << " headquarter stops making warriors" << endl;
		}
	private:
		string _name;
		int _life;
		int _curr;
		int _last_id;
		vector<string> _order;
		map<string, int> _warrior_count;
		map<string, int> _warrior_cost;
		vector<Warrior> _warriors;
		bool _isStopped;
		bool _isFirstStopped;
		
};

class Solution
{
	public:
		Solution() {
		}
		~Solution() {}

		void init()
		{
			int quarterNumber = sizeof(_QuarterNames)/sizeof(char*);
			for (int i=0; i<quarterNumber; i++)
			{
				_quarters.push_back(Quarter());
				_quarters[i].set_name(_QuarterNames[i]);
				if (i==0)
					_quarters[i].set_order(_OrderOfRed, 5);
				else if (i==1)
					_quarters[i].set_order(_OrderOfBlue, 5);

			}
		}

		void run()
		{
			int quarterNumber = sizeof(_QuarterNames)/sizeof(char*);
			int cases;
			cin >> cases;

			for (int i=0; i<cases; i++)
			{
				int life;
				int cost[5];
				cin >> life;
				for (int j=0; j<5; j++)
					cin >> cost[j];

				_time = 0;
				cout << "Case:" << i+1 << endl;
				for (int j=0; j<quarterNumber; j++)
				{
					_quarters[j].reset();
					_quarters[j].set_life(life);
					_quarters[j].set_cost(_StandardOrder, cost, 5);
				}

				bool flag;
				do 
				{
					flag = false;
					for (int j=0; j<quarterNumber; j++)
					{
						bool ret =  _quarters[j].next();
						_quarters[j].showProcess(_time);
						flag = flag || ret;
					}
					++_time;
				} while (flag);
			}
		}
	private:
		vector<Quarter> _quarters;
		int _time;

		static const char*  _QuarterNames[2];
		static const char*  _OrderOfRed[5];
		static const char*  _OrderOfBlue[5];
		static const char*  _StandardOrder[5];
};

const char*  Solution::_QuarterNames[2] = {"red", "blue"};
const char*  Solution::_OrderOfRed[5] = {"iceman", "lion", "wolf", "ninja", "dragon"};
const char*  Solution::_OrderOfBlue[5] = {"lion", "dragon", "ninja", "iceman", "wolf"};
const char*  Solution::_StandardOrder[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};


int main()
{
	try
	{
		Solution  sol;
		sol.init();
		sol.run();
	}
	catch (QuarterException& q)
	{
		return -1;
	}
	return 0;
}
