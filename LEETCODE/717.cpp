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
    bool isOneBitCharacter(vector<int>& bits) {
        bool is_one_bit = false;
        const int len = bits.size();
        for (int i=0; i<len; ) {
            if (bits[i] == 0) {
                ++i;
                is_one_bit = true;
            } else {
                i += 2;
                is_one_bit = false;
            }
        }
        return is_one_bit;
    }
};


int main() {
    std::vector<int> bits = {1,1,1,0};
    std::cout << Solution().isOneBitCharacter(bits) << std::endl;
    return 0;
}

