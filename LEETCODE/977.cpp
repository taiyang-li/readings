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

class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int len = A.size();
        if (len == 0) return std::vector<int>();
        int min_idx = 0;
        int min_value = std::abs(A[0]);
        for (int i=1; i<len; ++i) {
            if (abs(A[i]) < min_value) {
                min_value = abs(A[i]);
                min_idx = i;
            }
        }

        std::vector<int> ret;
        ret.push_back(A[min_idx] * A[min_idx]);
        int left = min_idx - 1;
        int right = min_idx + 1;
        while (left >=0 || right < len) {
            int tmp = INT_MAX;
            tmp = std::min(tmp, left >= 0 ? A[left] * A[left] : INT_MAX);
            tmp = std::min(tmp, right < len ? A[right] * A[right] : INT_MAX);
            ret.push_back(tmp);

            if (left >= 0 && tmp == A[left] * A[left]) {
                left--;
            } else {
                right++;
            }
        }
        return ret;
    }
}; 


int main() {
    std::vector<int> A = {-4,-1,0,3,10};
    auto ret = Solution().sortedSquares(A);
    for (auto x : ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
