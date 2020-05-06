#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

class CmpByHeight {
public:
    bool operator()(const pair<int, int>& left, const pair<int, int>& right) {
        if (left.first < right.first) {
            return false;
        } else if (left.first == right.first) {
            return std::less<int>()(left.second, right.second);
        } else {
            return true;
        }
    }
};

class Solution {
public:
    vector<pair<int, int> > reconstructQueue(vector<pair<int, int>>& people) {
        if (people.size() <= 1) {
            return people;
        }
        
        vector<pair<int, int> > ret;
        ret.reserve(people.size());
        std::sort(people.begin(), people.end(), CmpByHeight());
        for (auto x : people) {
            ret.insert(ret.begin() + x.second, x);
        }
        return ret;
    }
};


int main() {
    vector<pair<int, int> > input = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};
    vector<pair<int, int> > output = Solution().reconstructQueue(input);
    for (auto x : output) {
        std::cout << x.first << ", " << x.second << std::endl;
    }
    return 0;
}
