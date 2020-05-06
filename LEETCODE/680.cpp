#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
public:
    bool validPalindrome(const string& s) {
        int chances = 1;
        return doValidPalindrom(s, 0, s.size()-1, chances);
    }

    bool doValidPalindrom(const string& s, int left, int right, int& chances) {
        assert(left >= 0 && left < s.size());
        assert(right >= 0 && right < s.size());
        assert(chances >= 0);
        while (right > left && s[left] == s[right]) {
            left++;
            right--;
        }
        if (left >= right) {
            return true;
        }
        if (chances == 0) {
            return false;
        }
        chances--;
        int copy_chances = chances;
        return doValidPalindrom(s, left+1, right, chances) || doValidPalindrom(s, left, right-1, copy_chances);
    }
};

int main () {
    Solution solution;
    std::cout << solution.validPalindrome("abca") << std::endl;
    return 0;
}
