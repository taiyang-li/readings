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
    vector<int> sortArrayByParityII(vector<int>& A) {
        const int len = A.size();
        int even = 0;
        int odd = 1;
        while (even < len && odd < len) {
            while (even < len && A[even] % 2 == 0) {
                even += 2;
            }
            while (odd < len && A[odd] % 2 == 1) {
                odd += 2;
            }
            if (even < len && odd < len) {
                std::swap(A[even], A[odd]);
            }
        }
        return A;
    }
};

int main() {
    std::vector<int> A = {4,2,5,7};
    auto ret = Solution().sortArrayByParityII(A);
    std::for_each(ret.begin(), ret.end(), [](int n) {std::cout << n << std::endl;});
    return 0;
}

