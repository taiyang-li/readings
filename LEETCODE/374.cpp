#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int pick = 0;
int guess(int num) {
    std::cout << "pick: " << pick << ", num: " << num << std::endl; 
    if (pick < num) {
        return -1;
    } else if (pick == num) {
        return 0;
    } else {
        return 1;
    }
}

class Solution {
public:
    int guessNumber(int n) {
        int64_t left = 1;
        int64_t right = n;
        int64_t mid = 0;
        int hint = 0;
        while (left <= right) {
            mid = (left + right)/2;
            hint = guess(mid);
            if (hint == 0) {
                return mid;
            }
            
            if (hint > 0) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }
        return -1;
    }
};

int main() {
    int n = 2126753390;
    pick = 1702766719;
    std::cout << Solution().guessNumber(n) << std::endl;
    return 0;
}
