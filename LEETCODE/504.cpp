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
    string convertToBase7(int num) {
        if (num < 0) return "-" + helper(-num);
        else return helper(num);
    }

    string helper(int num) {
        if (num == 0) return "0";
        std::string ret;
        int a = num / 7;
        int b = num - 7 * a;
        if (a > 0) {
            ret += helper(a);
        }
        ret += b + '0';
        return ret;
    }
};

int main() {
    return 0;
}

