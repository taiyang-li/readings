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
    vector<int> numberOfLines(vector<int>& widths, const string& S) {
        int line = 1;
        int unit = 0;
        for (auto ch: S) {
            int width = widths[ch-'a'];
            if (unit + width > 100) {
                ++line;
                unit = width;
            } else {
                unit += width;
            }
        }
        return {line, unit};
    }
}; 
int main() {
    std::vector<int> widths = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
    string s = "abcdefghijklmnopqrstuvwxyz";
    auto ret = Solution().numberOfLines(widths, s);
    return 0;
}

