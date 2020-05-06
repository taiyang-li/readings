#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    bool rotateString(const string& A, const string& B) {
        const int len_a = A.size();
        const int len_b = B.size();
        if (len_a != len_b) {
            return false;
        }
        if (A.empty()) {
            return true;
        }

        size_t pos = B.find(A[0]);
        while (pos != std::string::npos) {
            int left_len = pos;
            int right_len = len_b - left_len;
            if (A.substr(0, right_len) == B.substr(pos, right_len) &&
                    A.substr(right_len, left_len) == B.substr(0, left_len)) {
                return true;
            }
            pos = B.find(A[0], pos+1);
        }
        return false;
    }
};

int main() {
    std::cout << Solution().rotateString("abcde", "cdeab") << std::endl;
    return 0;
}

