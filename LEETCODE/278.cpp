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

std::vector<int> is_bad = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

// Forward declaration of isBadVersion API.
bool isBadVersion(int version) {
    return is_bad[version-1] == 1;
}

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;
        int prev_left = -1;
        while (left <= right) {
            if (left != prev_left && isBadVersion(left)) {
                return left;
            }

            prev_left = left;
            auto mid = left + (right - left)/2;
            auto bad = isBadVersion(mid);
            if (bad) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};

int main() {
    return 0;
}

