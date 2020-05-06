#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <sstream>
#include <functional>
#include <cstdint>
#include <random>
#include <queue>

class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones) {
        std::priority_queue<int, std::vector<int>, std::less<int> > pq(stones.begin(), stones.end());
        while (pq.size() >= 2) {
            auto first = pq.top();
            pq.pop();

            auto second = pq.top();
            pq.pop();

            if (first < second) {
                pq.push(second - first);
            } else if (first > second) {
                pq.push(first - second);
            }
        }

        if (pq.size() == 1) {
            return pq.top();
        } else {
            return 0;
        }
    }
};

int main() {
    std::vector<int> stones = {2,7,4,1,8,1};
    std::cout << Solution().lastStoneWeight(stones) << std::endl;
    return 0;
}
