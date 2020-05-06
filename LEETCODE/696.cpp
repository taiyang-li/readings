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
    int countBinarySubstrings(const string& s) {
        const int len = s.size();
        std::vector<int> borders;
        borders.push_back(0);
        while (borders.back() < len) {
            int start = borders.back();
            int end = start+1;
            for (; end < len && s[end] == s[start]; ++end);
            borders.push_back(end);
        }

        const int border_len = borders.size();
        int ret = 0;
        for (int i=1; i<border_len-1; ++i) {
            ret += std::min(borders[i]-borders[i-1], borders[i+1]-borders[i]);
        }
        return ret;
    }
}; 

int main() {
    std::cout << Solution().countBinarySubstrings("00110011") << std::endl;
    return 0;
}

