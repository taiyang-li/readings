#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
using std::vector;

class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        std::sort(A.begin(), A.end());
        int len = A.size();
        for (int i=len-1; i>=2; --i) {
            if (A[i] < A[i-1] + A[i-2]) {
                return A[i] + A[i-1] + A[i-2];
            }
        }
        return 0;
    }
};
int main() {
    return 0;
}
