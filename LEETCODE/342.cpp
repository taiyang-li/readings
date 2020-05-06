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
    bool isPowerOfFour(int num) {
        return !(num & 0x80000000) && ! (num & (num-1)) && (num & 0x55555555);
    }
};

int main() {
    return 0;
}

