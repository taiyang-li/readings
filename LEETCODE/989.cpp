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
    vector<int> addToArrayForm(vector<int>& A, int K) {
        if (K == 0) {
            return A;
        }

        std::vector<int> B;
        while (K > 0) {
            B.push_back(K % 10);
            K /= 10;
        }

        std::reverse(A.begin(), A.end());
        int C = 0;
        int len_a = A.size();
        int len_b = B.size();
        std::vector<int> ret;
        for (int i=0; i<len_a || i<len_b; ++i) {
            int left = i < len_a ? A[i] : 0;
            int right = i < len_b ? B[i] : 0;
            ret.push_back((left+right+C) % 10);
            C = (left+right+C) / 10;
        }
        if (C > 0) {
            ret.push_back(C);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

};

int main() {
    std::vector<int> A = {1,2,0,0};
    int K = 34;
    auto ret = Solution().addToArrayForm(A, K);
    for (auto x:ret) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
