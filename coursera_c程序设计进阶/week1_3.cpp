#include <iostream>
#include <string>
#include <cstdio>
#include <map>

using namespace std;
int main()
{
	map<int, float> sum_by_id;
	map<string, float> sum_by_type;
	
	for (int i=0; i<3; ++i)
	{
		int id;
		cin >> id;

		int n;
		cin >> n;

		for (int i = 0; i < n; i++)
		{
			string type;
			float bill;
			cin >> type;
			cin >> bill;

			map<int, float>::iterator it1 = sum_by_id.find(id);
			if (it1 == sum_by_id.end())
				sum_by_id[id] = bill;
			else
				sum_by_id[id] += bill;

			map<string, float>::iterator it2 = sum_by_type.find(type);
			if (it2 == sum_by_type.end())
				sum_by_type[type] = bill;
			else
				sum_by_type[type] += bill;
		}
	}

  for (map<int, float>::iterator it = sum_by_id.begin(); it!=sum_by_id.end(); ++it)
		printf("%d %.2f\n", it->first, it->second);
  for(map<string, float>::iterator it = sum_by_type.begin(); it!=sum_by_type.end(); ++it)
		printf("%s %.2f\n", it->first.c_str(), it->second);
	return 0;
}
