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
#include <cstring> 
using std::vector;
using std::string;

class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        const int len = A.size();
        std::vector<char*> counts(len, NULL);
        for (auto& count: counts) {
            count = new char[26];
            ::memset(count, 0, 26);
        }

        for (int i=0; i<int(A.size()); ++i) {
            char* count = counts[i];
            for (auto ch: A[i]) {
                count[ch - 'a']++;
            }
        }

        std::vector<std::string> ret;
        for (int i=0; i<26; ++i) {
            int j = 0;
            int min_count = 100;
            for (; j<len; ++j) {
                if (counts[j][i] == 0) {
                    break;
                }

                if (counts[j][i] < min_count) {
                    min_count = counts[j][i];
                }
            }

            if (j != len) {
                continue;
            }

            char ch = 'a' + i;
            for (int k=0; k<min_count; ++k) {
                ret.push_back(std::string(1, ch));
            }
        }

        for (auto& count: counts) {
            delete [] count;
            count = NULL;
        }
        return ret;
    }
};


int main() {
    std::string S = "IDID";
    std::vector<std::string> A = {"bella","label","roller"};
    auto ret = Solution().commonChars(A);
    for (const auto& x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
