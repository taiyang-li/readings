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
    int getSum(int a, int b) {
        int carry = 0;
        int ret = 0;
        for (int i=0; i<32; ++i) {
            int bit = ((a >> i) & 1) + ((b >> i) & 1)  + carry;
            carry =  ((bit & 2) != 0) ? 1 : 0;
            bit &= 1;
            ret |= (bit << i);
        }
        return ret;
    }
};
int main() {
    std::cout << Solution().getSum(1,2) << std::endl;
    return 0;
}

