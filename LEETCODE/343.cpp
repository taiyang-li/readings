#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        vector<int> table(n+1, 0);
        for (int i=2; i<=n; ++i) {
            if (i == 2) {
                table[i] = 1;
                continue;
            }

            int tmp = INT_MIN;
            for (int left=1; left<=i-1; ++left) {
                tmp = std::max(tmp, left * table[i-left]);
                tmp = std::max(tmp, left * (i-left));
            }
            table[i] = tmp;
        }
        return table[n];
    }

    int helper(int n, int factor) {
        int quotient = n/factor;
        int remainder = n%factor;
        if (quotient == 0) {
            return 0;
        }
        int ret = 1;
        for (int i=0; i<quotient; ++i) {
            ret *= factor;
        }
        if (remainder > 0) {
            ret *= remainder;
        }
        return ret;
    }
};

int main() {
    for (int i=2; i<=58; ++i) {
        std::cout << i << ":" << Solution().integerBreak(i) << std::endl;
    }
    return 0;
}
