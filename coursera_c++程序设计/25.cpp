#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

typedef unsigned long long uint64_t;
map<uint64_t, int> all; 

set<uint64_t> values;
set<uint64_t>::iterator pre_iterator(set<uint64_t>::iterator it)
{
    set<uint64_t>::iterator ret = --it;
    ++it;
    return ret;
}

set<uint64_t>::iterator next_iterator(set<uint64_t>::iterator it)
{
    set<uint64_t>::iterator ret = ++it;
    --it;
    return ret;
}

int add_member(int id, uint64_t value)
{
    values.insert(value);
    all[value] = id;

    set<uint64_t>::iterator it = values.find(value);
    
    int nearest_value;
    int nearest_id;
    if (it == values.begin())
    {
        nearest_value = * (next_iterator(it));
    }
    else if (next_iterator(it) == values.end())
    {
        nearest_value = * (pre_iterator(it));
    }
    else
    {
        uint64_t left = * (pre_iterator(it));
        uint64_t right = * (next_iterator(it));
        nearest_value = (right-value) >= (value-left) ? left : right;
    }

    nearest_id = all[nearest_value];
    return nearest_id;
}

int main()
{
    values.insert(1000000000);
    all[1000000000] = 1; 

    int n;
    uint64_t value;
    int id, oppo_id;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> id;
        cin >> value;
        oppo_id = add_member(id, value);
        cout << id << " " << oppo_id << endl;
    }
    return 0;    
}
