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
    bool isUgly(int num) {
        if (num <= 0) return false;
        while (num != 1) {
            bool flag = false;
            if (num % 2 == 0) {
                num /= 2;
                flag = true;
            }
            if (num % 3 == 0) {
                num /= 3;
                flag = true;
            }
            if (num % 5 == 0) {
                num /= 5;
                flag = true;
            }
            if (! flag) {
                break;
            }
        }
        return num == 1;
    }
};

int main() {
    return 0;
}

