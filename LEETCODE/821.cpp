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
    vector<int> shortestToChar(const string& S, char C) {
        const int len = S.size();
        std::vector<int> ret(len, len);
        int last = -1;
        for (int i=0; i<len; ++i) {
            if (S[i] == C) {
                last = i;
            }

            if (last != -1) {
                ret[i] = i - last;
            }
        }

        last = len;
        for (int i=len-1; i>=0; --i) {
            if (S[i] == C) {
                last = i;
            }
           
            if (last != len) {
                ret[i] = std::min(ret[i], last-i);
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

