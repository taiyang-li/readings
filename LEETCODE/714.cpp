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
    int maxProfit(vector<int>& prices, int fee) {
        if (prices.empty()) {
            return 0;
        }
        
        vector<int> f(prices.size(), 0);
        f[0] = 0;
        int tmp = -prices[0];
        for (int k=1; k<int(prices.size()); ++k) {
            if (k >= 2) {
                tmp = std::max(tmp, f[k-2] - prices[k-1]);
            }
            f[k] = std::max(f[k-1], tmp + prices[k] - fee);
        }
        return *f.rbegin();
    }
};

int main() {
    std::vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    std::cout << Solution().maxProfit(prices, fee) << std::endl;
    return 0;
}
