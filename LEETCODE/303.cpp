#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
using namespace std;

class NumArray {
public:
    NumArray(const vector<int>& nums) {
        _sum_by_index[-1] = 0;
        for (int i=0; i<int(nums.size()); ++i) {
            _sum_by_index[i] = _sum_by_index[i-1] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        return _sum_by_index[j] - _sum_by_index[i-1];
    }
    
protected: 
    std::map<int, int> _sum_by_index;
};

int main() {
    std::vector<int> nums = {1,3,5};
    NumArray* obj = new NumArray(nums);
    std::cout << obj->sumRange(0, 2) << std::endl;
    std::cout << obj->sumRange(1, 2) << std::endl;
    return 0;
}
