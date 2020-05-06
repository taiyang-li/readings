#include <string> 
#include <iostream>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        if (arr.size() <= 1) {
            return;
        }

        int mid = -1;
        size_t new_len = 0;
        while (new_len < arr.size()) {
                new_len += arr[++mid] == 0 ? 2 : 1;
        }

        bool single_zero = new_len > arr.size();
        int right = arr.size() - 1;
        if (single_zero) {
            --mid;
            // std::cout << right << ":" << 0 << std::endl;
            arr[right--] = 0;
        }
        while (mid >= 0) {
            if (arr[mid] == 0) {
                // std::cout << right << ":" << 0 << std::endl;
                arr[right--] = 0;
                // std::cout << right << ":" << 0 << std::endl;
                arr[right--] = 0;
            } else {
                // std::cout << right << ":" << arr[mid] << std::endl;
                arr[right--] = arr[mid];
            }
            --mid;
        }
    }
};

int main() {
    std::vector<int> arr = {1,0,2,3,0,4,5,0};
    Solution().duplicateZeros(arr);
    for (auto x: arr) {
        std::cout << x << std::endl;
    }
    return 0;
}
 
 
