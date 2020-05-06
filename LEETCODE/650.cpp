#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <cmath>

using namespace std;

class Solution {
public:
    int minSteps(int n) {
        int ret = 0;
        map<int, int> factors;
        factoring(n, factors);
        for (auto& factor : factors) {
            ret += factor.first * factor.second;
        }
        return ret;
    }

    void factoring(int n, map<int, int>& factors) {
        if (n == 1) {
            return;
        }

        for (int i=2; i<=int(sqrt(n)) + 1; ++i) {
            if (n % i == 0) {
                factors[i]++;
                factoring(n/i, factors);
                return;
            }
        }
        factors[n]++;
    }
};

int main() {
    int n = 7;
    std::cout << Solution().minSteps(n) << std::endl;
}
