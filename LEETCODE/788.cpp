#include <iostream>
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
#include <map>

using namespace std;

class Solution {
public:
    int rotatedDigits(int N) {
        int weight = 1;
        int pow = 0;
        int pow_of_3 = 1;
        int pow_of_7 = 1;
        while (weight*10 <= N) {
            weight *= 10;
            pow_of_7 *= 7;
            pow_of_3 *= 3;
            pow++;
        }

        int ret = 0;
        int digit = 0;
        int co1 = 0;
        int co2 = 0;
        bool flag = true;
        vector<int> prefix_digits;
        while (pow >= 0) {
            digit = (N/weight) % 10;
            flag = is_all_speical_digit(prefix_digits, flag);
            
            co1 = good_digit_nums[digit];
            co2 = special_good_digit_nums[digit];
            if (flag) {
                ret += (co1 - co2) * pow_of_7 + co2 * (pow_of_7 - pow_of_3);
            } else {
                ret += co1 * pow_of_7;
            }

            if (good_digits.count(digit) == 0) {
                return ret;
            }

            weight /= 10;
            pow--;
            pow_of_3 /= 3;
            pow_of_7 /= 7;
            prefix_digits.push_back(digit);
        }
        flag = is_all_speical_digit(prefix_digits, flag);
        if (! flag) {
            ret += good_digits.count(digit);
        }
        return ret;
    }
    
    bool is_all_speical_digit(vector<int>& digits, bool prev_flag) {
        if (! prev_flag) {
            return false;
        }

        for (auto digit : digits) {
            if (special_good_digits.count(digit) == 0) {
                return false;
            }
        }
        return true;
    }

    static set<int> good_digits;
    static set<int> special_good_digits;
    static map<int, int> good_digit_nums;
    static map<int, int> special_good_digit_nums;
};

set<int> Solution::good_digits = {0, 1, 2, 5, 6, 8, 9};
set<int> Solution::special_good_digits = {0, 1, 8};
map<int, int> Solution::good_digit_nums = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 3}, {5, 3}, {6, 4}, {7, 5}, {8, 5}, {9, 6}};
map<int, int> Solution::special_good_digit_nums = {{0, 0}, {1, 1}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {8, 2}, {9, 3}};

int main() {
    Solution solution;
    std::cout << solution.rotatedDigits(9) << std::endl;
    return 0;
}
