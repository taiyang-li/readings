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
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int ret = 0;
        const size_t len = timeSeries.size();
        for (size_t i=0; i<len; ++i) {
            if (i == len-1) {
                ret += duration;
            } else {
                ret += std::min(timeSeries[i+1] - timeSeries[i], duration);
            }
        }
        return ret;
    }
};

int main() {
    std::vector<int> timeSeries = {1,4};
    int duration = 2;
    std::cout << Solution().findPoisonedDuration(timeSeries, duration) << std::endl;
    return 0;
}
