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
    vector<int> sortArrayByParity(vector<int>& A) {
        const int len = A.size();
        int mid = 0;
        int left = -1;
        for (; mid<len; ++mid) {
            if (A[mid] % 2 == 1) {
                continue;
            } else {
                std::swap(A[++left], A[mid]);
            }
        }
        return A;
    }
};

int main() {
    return 0;
}

