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
    bool canWinNim(int n) {
        return n > 0 && (n % 4 != 0);
    }
};
int main() {
    return 0;
}

