
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        bool isIdealPermutation(vector<int>& A) {
            vector<int> max_table(A.size(), 0);
            max_table[0] = A[0];
            max_table[1] = max(A[1], A[0]);
            for (size_t i=2; i<A.size(); ++i) {
                if (A[i] < max_table[i-2]) {
                    return false;
                }
                max_table[i] = max(A[i], max_table[i-1]);
            }
            return true;
        }
};

int main() {
    vector<int> A = {2, 0, 1};
    std::cout << Solution().isIdealPermutation(A) << std::endl;

    vector<int> B = {1, 2, 0};
    std::cout << Solution().isIdealPermutation(B) << std::endl;
    return 0;
}
