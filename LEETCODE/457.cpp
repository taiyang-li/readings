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
    bool circularArrayLoop(std::vector<int>& nums) {
        if (nums.empty()) {
            return false;
        }

        // std::vector<char> visited(nums.size(), 0);
        for (size_t i=0; i<nums.size(); ++i) {
            /*
            if (visited[i]) {
                continue;
            }
            */

            int direction = nums[i] > 0 ? 1 : -1;
            int start = i;
            int count = 0;
            int curr = i;
            int next = 0;
            while (1) {
                next = cal_next(curr, nums[curr], direction, nums);
                if (next == -1) {
                    break;
                }

                count++;
                curr = next;
                if (count == int(nums.size()) || curr == start) {
                    break;
                }
            }
            if (count > 0 && curr == start) {
                return true;
            }
        }
        return false;
    }

    inline int cal_next(int index, int step, int direction, std::vector<int>& nums) {
        int ret = index + step;
        while (ret < 0) {
            ret += nums.size();
        }
        ret %= nums.size();

        if (ret == index) {
            return -1;
        }
        if (direction * nums[ret] < 0) {
            return -1;
        }
        return ret;
    }
};

int main() {
    // std::vector<int> nums = {2, -1, 1, 2, 2};
    std::vector<int> nums = {-1, 2};
    std::cout << Solution().circularArrayLoop(nums) << std::endl;
    return 0;
}
