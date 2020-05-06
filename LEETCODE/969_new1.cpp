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
using std::vector;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        std::vector<int> ret;
        int n = A.size();
        int i = 0;
        int j = 0;
        for (i=n; i>=1; --i) {
            for (j=0; j<i; ++j) {
                if (A[j] == i) {
                    break;
                }
            }

            if (j+1 == i) {
                continue;
            }
            std::reverse(A.begin(), A.begin() + j + 1);
            std::reverse(A.begin(), A.begin() + i);
            ret.push_back(j+1);
            ret.push_back(i);
            for (auto x: A) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
        return ret;
    }
};

int main() {
    std::vector<int> A = {3,2,4,1};
    auto ret = Solution().pancakeSort(A) ;
    for (auto x: ret) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
