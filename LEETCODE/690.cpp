#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};


class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        _id2employee.clear();
        for (auto employee: employees) {
            _id2employee[employee->id] = employee;
        }
        return helper(id);
    }

    int helper(int id) {
        int ret = 0;
        auto employee = _id2employee[id];
        ret += employee->importance;
        for (auto subid: employee->subordinates) {
            ret += helper(subid);
        }
        return ret;
    }

private:
    std::unordered_map<int, Employee*> _id2employee;
}; 

int main() {
    return 0;
}

