#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
using std::vector;
using std::string;

class Solution {
public:
    int reachNumber(int target) {
        int m = std::abs(target);
        int ret = std::ceil((std::sqrt(1+8*m) - 1)/2);
        while ((ret * (ret + 1) / 2) % 2 != m % 2 ) {
            ret++;
        }
        return ret;
    }
};

int main() {
    std::cout << Solution().reachNumber(5) << std::endl;
    return 0;
}
