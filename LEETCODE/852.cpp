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
    int peakIndexInMountainArray(vector<int>& A) {
        const int len = A.size();
        int left = 0;
        int right = len-1;
        int mid = 0;
        while (left <= right) {
            mid = (left + right)/2;
            if (mid == len - 1 || mid == 0) {
                return -1;
            } else if (A[mid-1] < A[mid] && A[mid+1] < A[mid]) {
                return mid;
            } else if (A[mid-1] < A[mid]) {
                left = mid+1;
            } else if (A[mid+1] < A[mid] ) {
                right = mid-1;
            }
        }
        return -1;
    }
};

int main() {
    std::vector<int> nums1 = {0,1,0};
    std::cout << Solution().peakIndexInMountainArray(nums1) << std::endl;

    std::vector<int> nums2 = {0,2,1,0};
    std::cout << Solution().peakIndexInMountainArray(nums2) << std::endl;
    return 0;
}
