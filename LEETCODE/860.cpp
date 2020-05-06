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
    bool lemonadeChange(vector<int>& bills) {
        int s5 = 0;
        int s10 = 0;
        for (auto bill: bills) {
            if (bill == 5) {
                ++s5;
            } else if (bill == 10) {
                if (s5 == 0) {
                    return false;
                }
                --s5;
                ++s10;
            } else if (bill == 20) {
                if (s10 > 0) {
                    if (s5 == 0) {
                        return false;
                    }
                    --s10;
                    --s5;
                } else {
                    if (s5 < 3) {
                        return false;
                    }
                    s5 -= 3;
                }
            }
        }
        return true;
    }
};

int main() {
    return 0;
}

