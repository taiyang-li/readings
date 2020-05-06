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
    vector<int> selfDividingNumbers(int left, int right) {
        std::vector<int> ret;
        for (int n=left; n<=right; ++n) {
            if (helper(n)) {
                ret.push_back(n);
            }
        }
        return ret;
    }
    
    bool helper(int n) {
        int digit = 0;
        int old_n = n;
        while (n > 0) {
            digit = n % 10;
            if (digit == 0 || old_n % digit != 0) {
                return false;
            }
            n /= 10;
        }
        return true;
    }
};

int main() {
}
