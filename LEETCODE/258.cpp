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
    int addDigits(int num) {
        for (; num >= 10; num = helper(num));
        return num;
    }

    int helper(int num) {
        int ret = 0;
        while (num > 0) {
            ret += num % 10;
            num /= 10;
        }
        return ret;
    }
};

int main() {
    std::cout << Solution().addDigits(38);
    return 0;
}
