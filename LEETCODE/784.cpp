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
    vector<string> letterCasePermutation(const string& S) {
        int count = 0;
        for (auto ch: S) {
            if (std::isalpha(ch)) {
                ++count;
            }
        }

        int permutations = 1 << count;
        std::vector<std::string> ret(permutations, S);
        for (int i=0; i<permutations; ++i) {
            transform_by_bitmap(ret[i], i);
        }
        return ret;
    }
    
    void transform_by_bitmap(string& s, int bitmap) {
        int curr = s.size() - 1;
        while (bitmap > 0 && curr >= 0) {
            while (curr >= 0 && ! std::isalpha(s[curr])) --curr;
            if (bitmap & 1) {
                if (s[curr] >= 'a' && s[curr] <= 'z') {
                    s[curr] -= 'a' - 'A';
                } else {
                    s[curr] += 'a' - 'A';
                }
            }
            bitmap >>= 1;
            --curr;
        }
    }
};

int main() {
    std::string S = "C";
    auto ret = Solution().letterCasePermutation(S);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}

