#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <random>
using namespace std;

class Solution {
public:
    Solution(vector<int> nums) : _origin_nums(nums) {
        ::srand(::time(NULL));
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return _origin_nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        std::vector<int> ret(_origin_nums);
        if (ret.empty()) {
            return ret;
        }

        for (int i=int(ret.size()-1); i>0; i--) {
            std::swap(ret[i], ret[rand()%(i+1)]);
        }
        return ret;
    }

private:
    std::vector<int> _origin_nums;
};


int main() {
    vector<int> nums = {1,2,3};
    Solution obj = Solution(nums);
    vector<int> param_1 = obj.shuffle();
    for (auto x: param_1) {
        std::cout << x << std::endl;
    }
    vector<int> param_2 = obj.reset();
    for (auto x: param_2) {
        std::cout << x << std::endl;
    }
    return 0;
}
