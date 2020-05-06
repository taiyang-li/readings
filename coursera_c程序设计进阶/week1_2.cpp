#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <iostream>
using namespace std;

bool checkRank(map<string, int>& rank_by_lake)
{
	int flag[4] = { 0, 0, 0, 0 };
	for (map<string, int>::iterator mit = rank_by_lake.begin(); mit != rank_by_lake.end(); ++mit)
	{
		int rank = mit->second;
		if (flag[rank - 1])
			return false;
		flag[rank - 1] = 1;
	}
	return true;
}

bool conditionA(map<string, int>& rank_by_lake)
{
	int count = 0;
	if (rank_by_lake["dongting"] == 1)
		count++;
	if (rank_by_lake["hongze"] == 4)
		count++;
	if (rank_by_lake["poyang"] == 3)
		count++;
	return count == 1;
}

bool conditionB(map<string, int>& rank_by_lake)
{
	int count = 0;
	if (rank_by_lake["hongze"] == 1)
		count++;
	if (rank_by_lake["dongting"] == 4)
		count++;
	if (rank_by_lake["poyang"] == 2)
		count++;
	if (rank_by_lake["tai"] == 3)
		count++;
	return count == 1;
}

bool conditionC(map<string, int>& rank_by_lake)
{
	int count = 0;
	if (rank_by_lake["hongze"] == 4)
		count++;
	if (rank_by_lake["dongting"] == 3)
		count++;
	return count == 1;
}

bool conditionD(map<string, int>& rank_by_lake)
{
	int count = 0;
	if (rank_by_lake["poyang"] == 1)
		count++;
	if (rank_by_lake["tai"] == 4)
		count++;
	if (rank_by_lake["hongze"] == 2)
		count++;
	if (rank_by_lake["dongting"] == 3)
		count++;
	return count == 1;
}


int main()
{
	map<string, int> rank_by_lake;
	rank_by_lake["poyang"] = 0;
	rank_by_lake["dongting"] = 0;
	rank_by_lake["tai"] = 0;
	rank_by_lake["hongze"] = 0;
	for (rank_by_lake["poyang"] = 1; rank_by_lake["poyang"] <= 4; rank_by_lake["poyang"]++)
	{
		for (rank_by_lake["dongting"] = 1; rank_by_lake["dongting"] <= 4; rank_by_lake["dongting"]++)
		{
			for (rank_by_lake["tai"] = 1; rank_by_lake["tai"] <= 4; rank_by_lake["tai"]++)
			{
				for (rank_by_lake["hongze"] = 1; rank_by_lake["hongze"] <= 4; rank_by_lake["hongze"]++)
				{
					if (checkRank(rank_by_lake) && conditionA(rank_by_lake) &&
						conditionB(rank_by_lake) && conditionC(rank_by_lake) &&
						conditionD(rank_by_lake))
					{
						cout << rank_by_lake["poyang"] << endl;
						cout << rank_by_lake["dongting"] << endl;
						cout << rank_by_lake["tai"] << endl;
						cout << rank_by_lake["hongze"] << endl;
					}
				}
			}
		}
	}
	// getchar();
	return 0;
}
