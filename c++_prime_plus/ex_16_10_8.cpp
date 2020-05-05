#include <iostream>
#include <cstdlib>
#include <ctime>   
#include <queue>
#include <string>
#include <algorithm> 
#include <functional>

using namespace std; 

template <class T>
void my_print(const T &t)
{
	cout << t << endl;
}

int main()
{
	vector<string> mat_friends;
	vector<string> pat_friends;
	vector<string> friends; 

	string temp;
	
	cout << "mat, please input your friends' name(empty line to quit): " << endl;
	while (getline(cin, temp) && !temp.empty())
		mat_friends.push_back(temp);

	cout << "pat, please input your friends' name(empty line to quit): " << endl;
	while (getline(cin, temp) && !temp.empty())
		pat_friends.push_back(temp);


	friends = mat_friends;
	for (auto it = pat_friends.begin(); it!=pat_friends.end(); ++it)
		friends.push_back(*it);
	
	sort(friends.begin(), friends.end());
	auto it = unique(friends.begin(), friends.end());
	friends.resize(distance(friends.begin(), it));
	for_each(friends.begin(), friends.end(), my_print<string>); 

	system("pause");
	return 0;
}



