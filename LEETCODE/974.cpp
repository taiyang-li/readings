#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
using std::vector;

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        std::vector<int> count(K, 0);
        count[0] = 1;
        int sum = 0;
        int remainder = 0;
        int ret = 0;
        for (auto a: A) {
            sum += a;
            remainder = ((sum % K) + K) % K;
            ret += count[remainder];
            count[remainder]++;
        }
        return ret;
    }
};
int main() {
    std::vector<int> A = {4,5,0,-2,-3,1};
    std::cout << Solution().subarraysDivByK(A, 5) << std::endl;
    return 0;
}
