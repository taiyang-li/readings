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
    string toLowerCase(const string str) {
        std::string ret(str);
        std::for_each(ret.begin(), ret.end(), [](char& ch){ch = std::tolower(ch);});
        return ret;
    }

    string toLowerCase1(const string str) {
        std::string ret(str);
        // std::transform(str.begin(), str.end(), ret.begin(), [](int n) -> int {return std::tolower(n);});
        std::transform(str.begin(), str.end(), ret.begin(), ::tolower);
        return ret;
    }


};

int main() {
    return 0;
}

