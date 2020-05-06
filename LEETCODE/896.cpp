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
    bool isMonotonic(vector<int>& A) {
        const int len = A.size();
        if (len <= 1) {
            return true;
        }

        int delta = A[1] - A[0];
        for (int i=1; i<len-1; ++i) {
            if (A[i+1] - A[i] == 0) {
                continue;
            }

            if (delta * (A[i+1] - A[i]) < 0) {
                return false;
            }
            delta = A[i+1] - A[i];
        }
        return true;
    }
};

int main() {
    std::vector<int> A = {11,11,9,4,3,3,3,1,-1,-1,3,3,3,5,5,5};
    std::cout << Solution().isMonotonic(A) << std::endl;
    return 0;
}

