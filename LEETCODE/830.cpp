#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    vector<vector<int> > largeGroupPositions(const string& S) {
        const int len = S.size();
        if (len <= 2) return {};

        int start = 0;
        int count = 0;
        std::vector<std::vector<int> > ret;
        int i = 0;
        for (; i<len; ++i) {
            if (i == 0) {
                start = 0;
                count = 1;
                continue;
            }
            
            if (S[i] == S[i-1]) {
                count++;
                continue;
            }

            if (count >= 3) {
                ret.push_back({});
                ret.rbegin()->push_back(start);
                ret.rbegin()->push_back(i-1);
            }
            start = i;
            count = 1;
        }
        if (count >= 3) {
            ret.push_back({});
            ret.rbegin()->push_back(start);
            ret.rbegin()->push_back(i-1);
        }
        return ret;
    }
};
int main() {
    std::string S = "abcdddeeeeaabbbcd";
    auto ret = Solution().largeGroupPositions(S);
    for (const auto& x : ret) {
        std::cout << x[0] << " " << x[1] << std::endl;
    }
    return 0;
}
