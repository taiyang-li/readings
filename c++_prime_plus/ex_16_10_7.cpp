#include <iostream>
#include <cstdlib>
#include <ctime>   
#include <queue>

using namespace std; 

vector<int> Lotto(int m, int n);
void my_print(int i) {cout << i << " ";}
int main()
{	
	vector<int> winners = Lotto(51, 6);
	for_each(winners.begin(), winners.end(), my_print);
	system("pause");
	return 0;
}


vector<int> Lotto(int m, int n)
{
	vector<int> choice;
	vector<int> res;
	
	for (int i=1; i<=m; i++)
		choice.push_back(i);
	
	for (int i=1; i<=n; i++)
	{
		random_shuffle(choice.begin(), choice.end());
		res.push_back(choice[0]);
		choice.erase(choice.begin());
	}
	return res;
}


