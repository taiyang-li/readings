#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;
using std::map;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        map<int, int> tb;
        vector<int> res;
        int len = numbers.size();
        for (int i=0; i<len; i++)
        {
            if(tb.find(numbers[i]) == tb.end())
                tb[target-numbers[i]] = i;
            else
            {
                res.push_back(tb[numbers[i]]+1);
                res.push_back(i+1);
                return res;
            }
        }
        return res;
    }
};

int main() {
    return 0;
}

