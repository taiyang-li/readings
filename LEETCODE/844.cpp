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
#include <cstring>
using std::vector;
using std::string;

class Solution {
public:
    bool backspaceCompare(string& S, string& T) {
        int lens = convert(S);
        int lent = convert(T);
        if (lens != lent) {
            return false;
        }
        return ::memcmp(S.c_str(), T.c_str(), lens) == 0;
    }
    
    int convert(string& s) {
        const int len = s.size();
        int left = -1;
        int mid = 0;
        while (mid < len) {
            if (s[mid] != '#') {
                s[++left] = s[mid];
            } else {
                if (left >= 0) {
                    --left;
                }
            }
            ++mid;
        }
        return left+1;
    }
};

int main() {
    std::string S = "ab#c";
    std::string T = "ad#c";
    std::cout << Solution().backspaceCompare(S, T) << std::endl;
    return 0;
}

