#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) : _nums(nums.begin(), nums.end()) {}
    
    void update(int i, int val) {
        _nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        int ret = 0;
        while (i<=j) {
            ret += _nums[i];
            ++i;
        }
        return ret;
    }

protected:
    std::vector<int> _nums;
};


int main() {
    std::vector<int> nums = {1,3,5};
    NumArray* obj = new NumArray(nums);
    std::cout << obj->sumRange(0, 2) << std::endl;
    obj->update(1, 2);
    std::cout << obj->sumRange(0, 2) << std::endl;
    return 0;
}
