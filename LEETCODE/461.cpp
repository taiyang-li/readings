#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int tmp = x ^ y;
        int ret = 0;
        while (tmp != 0) {
            tmp = tmp & (tmp-1);
            ++ret;
        }
        return ret;
    }
};

int main() {
    return 0;
}

