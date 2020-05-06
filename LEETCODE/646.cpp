#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class CmpByPair {
    public: 
        bool operator()(const std::vector<int>& left, const std::vector<int>& right) {
            if (left[0] < left[0]) {
                return true;
            } else if (left[0] == right[0]) {
                return std::less<int>()(left[1], right[1]);
            } else {
                return false;
            }
        }
};
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if (pairs.empty()) {
            return 0;
        }
        const int len = pairs.size();
        std::sort(pairs.begin(), pairs.end(), CmpByPair());
        std::vector<std::pair<int, int> > table(len, std::make_pair(0, 0));
        table[0].first = 1;
        table[1].second = pairs[0][1];
        std::pair<int, int> tmp;
        for (int i=1; i<len; ++i) {
            // 不选当前位置作为pair chain
            tmp = table[i-1];

            // 选取当前位置作为pair chain
            int j = i - 1;
            for (; j>=0; --j) {
                if (table[j].second < pairs[i][0]) {
                    break;
                }
            }
            if (j >= 0) {
                if (table[j].first + 1 > tmp.first) {
                    tmp.first = table[j].first + 1;
                    tmp.second = pairs[i][1];
                }
            } 
            table[i] = tmp;
        }
        return table[len-1].first;
    }
};

int main() {
    std::vector<std::vector<int> > pairs = {{1,2}, {2,3}, {3,4}};
    std::cout << Solution().findLongestChain(pairs) << std::endl;
    return 0;
}
