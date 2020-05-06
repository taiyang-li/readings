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
    bool hasAlternatingBits(int n) {
        int next = -1;
        while (n) {
            int bit = n & 1;
            if (next >= 0 && bit != next) {
                return false;
            }
            
            n >>= 1;
            next = 1 - bit;
        }
        return true;
    }
};

int main() {
    return 0;
}

