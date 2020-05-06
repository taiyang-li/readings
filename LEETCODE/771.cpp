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
    int numJewelsInStones(const string& J, const string& S) {
        // build index
        char tb[128] = {0};
        for (auto ch: J) {
            tb[size_t(ch)] = 1;
        }

        int ret = 0;
        for (auto ch: S) {
            if (tb[size_t(ch)] != 0) {
                ++ret;
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

