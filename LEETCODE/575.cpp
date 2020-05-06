#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
using namespace std;

class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        const int len = candies.size();
        if (len == 0) return 0;
        
        std::set<int> candy_set(candies.begin(), candies.end());
        const int set_len = candy_set.size();
        return std::min(len/2, set_len);
    }
};

int main() {
    return 0;
}
