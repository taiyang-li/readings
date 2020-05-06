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
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) return true;
        
        const int len = flowerbed.size();
        for (int i=0; i<len && n > 0; ++i) {
            if (flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) 
                    && (i == len-1 || flowerbed[i+1] == 0)) {
                flowerbed[i] = 1;
                --n;
            }
        }
        return n == 0;
    }
};
int main() {
    std::vector<int> flowerbed = {0,0,1,0,0};
    std::cout << Solution().canPlaceFlowers(flowerbed, 1) << std::endl;
    return 0;
}

