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
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 10;
        }
        if (n > 10) {
            return countNumbersWithUniqueDigits(10);
        } 

        int ret = 1;
        ret *= 9;
        for (int i=0; i<n-1; ++i) {
            ret *= 9 - i;
        }
        ret += countNumbersWithUniqueDigits(n-1);
        return ret;
    }
};

int main() {
    std::cout << Solution().countNumbersWithUniqueDigits(2) << std::endl;
    return 0;
}
