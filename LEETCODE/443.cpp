#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    int compress(std::vector<char>& chars) {
        const int len = chars.size();
        int left = -1;
        int right = 0;
        int cnt = 0;
        while (right < len) {
            char prev = chars[right];
            for (cnt = 0; right < len && chars[right] == prev; ++right, ++cnt);
            chars[++left] = prev;
            if (cnt >= 2) {
                std::string str_cnt = std::to_string(cnt);
                for (int i=0; i<int(str_cnt.size()); ++i) {
                    chars[++left] = str_cnt[i];
                }
            }
        }
        return left+1;
    }
};
int main() {
    // std::string a = "aabbccc";
    // std::cout << Solution().compress(a) << std::endl;
    return 0;
}

