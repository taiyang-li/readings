#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
#include <vector>
using std::vector;
using std::string;


class Solution {
public:
    vector<int> diStringMatch(const string& S) {
        const int N = S.size() + 1;
        std::vector<int> ret(N, 0);
        int l = 0;
        int r = N-1;
        for (int i=0; i<int(S.size()); ++i) {
            if (S[i] == 'I') {
                ret[i] = l++;
            }
            if (S[i] == 'D') {
                ret[i] = r--;
            }
        }
        ret[N-1] = l;
        return ret;
    }
}; 
int main() {
    std::string S = "IDID";
    auto ret = Solution().diStringMatch(S);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
