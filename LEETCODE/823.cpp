#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
using namespace std;

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        if (A.empty()) {
            return 0;
        }

        uint64_t ret = 0;
        std::set<int> nums(A.begin(), A.end());
        std::map<int, uint64_t> table;
        for (auto it=nums.begin(); it!=nums.end(); ++it) {
            uint64_t tmp = 1;
            for (auto prev_it = nums.begin(); prev_it != it && *prev_it <= int(std::sqrt(*it)); ++prev_it) {
                if (*it % *prev_it == 0 && table.count(*it / *prev_it) > 0) {
                    int left = *prev_it;
                    int right = *it / *prev_it;
                    if (left == right) {
                        tmp += table[left] * table[right];
                    } else {
                        tmp += 2 * table[left] *  table[right];
                    }
                }
            }
            table[*it] = tmp;
            ret += tmp;
        }
        return ret % int(1e9 + 7);
    }
};

int main() {
    std::vector<int> A = {46,144,5040,4488,544,380,4410,34,11,5,3063808,5550,34496,12,540,28,18,13,2,1056,32710656,31,91872,23,26,240,18720,33,49,4,38,37,1457,3,799,557568,32,1400,47,10,20774,1296,9,21,92928,8704,29,2162,22,1883700,49588,1078,36,44,352,546,19,523370496,476,24,6000,42,30,8,16262400,61600,41,24150,1968,7056,7,35,16,87,20,2730,11616,10912,690,150,25,6,14,1689120,43,3128,27,197472,45,15,585,21645,39,40,2205,17,48,136};
    // std::vector<int> A = {2, 4, 5, 10};
    std::cout << Solution().numFactoredBinaryTrees(A) << std::endl;
    return 0;
}
