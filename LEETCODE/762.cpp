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
    int countPrimeSetBits(int L, int R) {
        int ret = 0;
        int i = L;
        while ( i <= R) {
            int tmp = i;
            int set_bits = 0;
            for (; tmp > 0; ++set_bits) {
                tmp &= (tmp-1);
            }
            ret += _IS_PRIME[set_bits];

            ++i;
        }
        return ret;
    }

private:
    static constexpr int8_t _IS_PRIME[21] = 
    {
        // 0 1 2 3 4 
        0, 0, 1, 1, 0, \
        // 5 6 7 8 9
        1, 0, 1, 0, 0, \
        // 10 11 12 13 14
        0, 1, 0, 1, 0, \
        // 15 16 17 18 19
        0, 0, 1, 0, 1, \
        // 20
        0
    };

};



int main() {
    return 0;
}

