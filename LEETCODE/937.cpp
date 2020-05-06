#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
using std::vector;
using std::string;

class LetterLogCompare {
    public:
        bool operator()(const std::string& left, const std::string& right) {
            size_t left_pos = left.find(' ');
            size_t right_pos = right.find(' ');
            size_t left_idx = left_pos + 1;
            size_t right_idx = right_pos + 1;
            for (; left_idx < left.size() && right_idx < right.size(); ++left_idx, ++right_idx) {
                    if (left[left_idx] < right[right_idx]) {
                        return true;
                    } else if (left[left_idx] > right[right_idx]) {
                        return false;
                    }
            }

            if (right_idx < right.size() ) {
                return true;
            } else {
                return false;
            }
        }
};
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        int len = logs.size();

        // 将digit logs放到末尾
        int mid = len - 1;
        int right = len - 1;
        while (mid >= 0 && right >= 0) {
            while (right >= 0 && ! is_letter_log(logs[right])) {
                right--;
            }

            if (mid >= right) {
                mid = right - 1;
            }
            while (mid >= 0 && is_letter_log(logs[mid])) {
                mid--;
            }

            if (mid >= 0 && right >= 0) {
                std::swap(logs[mid], logs[right]);
            }
        }

        int num_letter_log = right + 1;
        std::sort(logs.begin(), logs.begin() + num_letter_log, LetterLogCompare());
        return logs;
    }

    bool is_letter_log(const std::string& log) {
        size_t pos = log.find(' ');
        if (pos == std::string::npos) {
            return false;
        }

        if (pos + 1 == log.size()) {
            return false;
        }

        return std::isalpha(log[pos+1]);
    }
}; 

int main() {
    // std::vector<std::string> logs = {"a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"};
    std::vector<std::string> logs = {"j mo", "5 m w", "g 07", "o 2 0", "t q h"};
    auto ret = Solution().reorderLogFiles(logs);
    for (const auto& x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
