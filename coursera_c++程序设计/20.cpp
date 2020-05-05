#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

class List
{
	public:
		List(int id) : _id(id) {}
		~List() {}

		void add_num(int n)
		{
			_nums.push_back(n);
		}

		void unique()
		{
			set<int> appear;
			for (vector<int>::iterator it = _nums.begin(); it != _nums.end(); ++it)
			{
				if (appear.find(*it) == appear.end())
				{
					appear.insert(*it);
				}
				else
				{
					it = _nums.erase(it);
					--it;
				}
			}
		}

		void out()
		{
			sort(_nums.begin(), _nums.end());
			for (vector<int>::iterator it = _nums.begin(); it != _nums.end(); it++)
			{
				cout << *it << " ";
			}
			cout << endl;
		}
		
		friend void merge(List& l1, List& l2)
		{
			for (vector<int>::iterator it = l2._nums.begin(); it != l2._nums.end(); ++it)
			{
				l1._nums.push_back(*it);
			}
			l2._nums.clear();
		}
	private:
		int _id;
		vector<int> _nums;
};

bool in_map(map<int, List*>& m, int k)
{
	if (m.find(k) != m.end())
		return true;
	else
		return false;
}
int main()
{	
	map<int, List*> id_list_map;		
	int id1;
	int id2;
	int num;
	string op;
	int commands;

	cin >> commands;
	while (commands--)
	{
		cin >> op;			
		if (op == "new")
		{
			cin >> id1;
			if (in_map(id_list_map, id1))
			{
				cerr << "list alreday exist" << endl;
				continue;
			}
			id_list_map[id1] = new List(id1);	
		}
		else if (op == "add")
		{
			cin >> id1;
			cin >> num;
			if (! in_map(id_list_map, id1))
			{
				cerr << "list not exist" << endl;
				continue;
			}
			id_list_map[id1]->add_num(num);
		}
		else if (op == "merge")
		{
			cin >> id1;
			cin >> id2;
			if ( ! in_map(id_list_map, id1)  ||   ! in_map(id_list_map, id2))
			{
				cerr << "list not exist" << endl;
				continue;
			}
			merge(*(id_list_map[id1]), *(id_list_map[id2]));
		}
		else if (op == "unique")
		{
			cin >> id1;
			if (! in_map(id_list_map, id1))
			{
				cerr << "list not exist" << endl;
				continue;
			}
			id_list_map[id1]->unique();	
		}
		else if (op == "out")
		{
			cin >> id1;
			if (! in_map(id_list_map, id1))
			{
				cerr << "list not exist" << endl;
				continue;
			}
			id_list_map[id1]->out();	
		}
		else
		{
			cerr << "WRONG COMMAND" << endl;
		}
	}

	return 0;
}
