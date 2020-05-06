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
    bool checkPerfectNumber(int num) {
        if (num <= 1) return false;
        int sum = 1;
        int sq = std::sqrt(num);
        for (int i=2; i<=sq; ++i) {
            if (num % i == 0) {
                if (i != num/i) {
                    sum += i;
                    sum += num / i;
                } else {
                    sum += i;
                }
            }
        }
        return num == sum;
    }
};

int main() {
    std::cout << Solution().checkPerfectNumber(28) << std::endl;
    return 0;
}

