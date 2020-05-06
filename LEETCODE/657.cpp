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

class Solution {
public:
    bool judgeCircle(const string& moves) {
        int x = 0;
        int y = 0;
        for (auto ch: moves) {
            auto delta = DELTA_BY_DIRECTION[ch];
            x += delta.first;
            y += delta.second;
        }
        return x == 0 && y == 0;
    }
    static std::map<char, std::pair<int, int> > DELTA_BY_DIRECTION;
};

std::map<char, std::pair<int, int> > Solution::DELTA_BY_DIRECTION = 
    {{'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};

int main() {
    return 0;
}

