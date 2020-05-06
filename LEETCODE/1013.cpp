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
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = std::accumulate(A.begin(), A.end(), 0);
        if (sum % 3 != 0) {
            return false;
        }

        bool found1 = false;
        bool found2 = false;
        int curr_sum = 0;
        for (auto x: A) {
            curr_sum += x;
            if (! found1 && ! found2 && curr_sum == sum/3) {
                found1 = true;
            }
            if (found1 && ! found2 && curr_sum == 2*sum/3) {
                found2 = true;
            }
        }
        return found1 && found2;
    }
};

int main() {
    return 0;
}

