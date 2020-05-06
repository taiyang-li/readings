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
    int largestSumAfterKNegations(vector<int>& A, int K) {
        const int len = A.size();
        int sum = std::accumulate(A.begin(), A.end(), 0);
        std::vector<int> profit(len, 0);
        std::transform(A.begin(), A.end(), profit.begin(), [](int x) -> int {return -2 * x;});
        std::sort(profit.begin(), profit.end());
        auto lower_it = std::lower_bound(profit.begin(), profit.end(), 0);
        auto upper_it = std::upper_bound(profit.begin(), profit.end(), 0);
        bool has_zero_profits = (upper_it != lower_it);
        int positive_profits = profit.end() - upper_it;
        if (K <= positive_profits) {
            sum = std::accumulate(profit.end()-K, profit.end(), sum);
        } else {
            int tmp = K - positive_profits;
            if (tmp % 2 == 0 || has_zero_profits) {
                sum = std::accumulate(upper_it, profit.end(), sum);
            } else {
                sum = std::accumulate(upper_it, profit.end(), sum);
                int tmp = INT_MIN;
                if (upper_it != profit.end()) {
                    tmp = -*upper_it;
                } 
                if (upper_it != profit.begin()) {
                    tmp = std::max(tmp, *(upper_it-1));
                }
                sum += tmp;
            }
        }
        return sum;
    }
};
int main() {
    return 0;
}

