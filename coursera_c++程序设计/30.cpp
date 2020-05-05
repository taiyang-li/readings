#include <iostream>
#include <map>

using namespace std;

map<int, int> num_set;

void process()
{
    string cmd;
    int tmp;
    cin >> cmd;
    cin >> tmp;
    if (cmd == "add")
    {
        num_set[tmp]++; 
        cout << num_set[tmp] << endl;
    }
    else if (cmd == "ask")
    {
        if (num_set.find(tmp) != num_set.end())
            cout << 1 << " " << num_set[tmp] << endl;
        else 
            cout << 0 << " " << 0 << endl;
    }
    else if (cmd == "del")
    {
        if (num_set.find(tmp) != num_set.end())
        {
            cout << num_set[tmp] << endl;
            num_set[tmp] = 0;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    else 
    {
        cout << "wrong command" << endl;
    }
}
int main()
{
    int n; 
    cin >> n;

    while (n--)
    {
        process();
    }
    return 0;
}

