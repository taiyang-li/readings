#include <string> 
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        int min_n = std::ceil((std::sqrt(candies*8.0+9.0) - 3.0)/2.0);
        int n = min_n;
        for (; n*(n+1)/2 <= candies; ++n);
        --n;
        int left = candies - n*(n+1)/2;
        std::vector<int> ret(num_people, 0);
        for (int i=1; i<=n; ++i) {
            ret[(i-1)%num_people] += i;
        }
        ret[n%num_people] += left;
        return ret;
    }
};

int main() {
    auto ret = Solution().distributeCandies(1000000000 , 3);
    /*
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    */
    return 0;
}
 
