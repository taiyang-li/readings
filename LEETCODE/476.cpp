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
    int findComplement(int num) {
        int mask = 1;
        while (mask < num) {
            mask <<= 1;
            mask += 1;
        }
        return mask ^ num;
    }
};

int main() {
    return 0;
}

