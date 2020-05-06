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
#include <utility>
using std::vector;
using std::string;

class Solution {
public:
    string reverseVowels(const string& s) {
        std::string ret(s);
        const int len = s.size();
        int left = 0;
        int right = len-1;
        while (left < right) {
            while (left < right && TARGET.find(ret[left]) == std::string::npos) {
                ++left;
            }
            while (left < right && TARGET.find(ret[right]) == std::string::npos) {
                --right;
            }
            if (left < right) {
                std::swap(ret[left++], ret[right--]);
            }
        }
        return ret;
    }

private:
    static const std::string TARGET;
};
const std::string Solution::TARGET = "aeiouAEIOU";

int main() {
    return 0;
}

