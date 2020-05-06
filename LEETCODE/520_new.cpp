#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <string>

using namespace std;

class Solution {
public:
    bool detectCapitalUse(const string& word) {
        // all not capital
        if (::islower(word[0])) {
            for (auto ch : word) {
                if (::isupper(ch)) {
                    return false;
                }
            }
            return true;
        }

        // all capital
        if (::isupper(word[1])) {
            for (size_t i=2; i<word.size(); ++i) {
                if (::islower(word[i])) {
                    return false;
                }
            }
            return true;
        }

        for (size_t i=2; i<word.size(); ++i) {
            if (::isupper(word[i])) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    std::cout << s.detectCapitalUse("USA") << std::endl;
    std::cout << s.detectCapitalUse("leetcode") << std::endl;
    std::cout << s.detectCapitalUse("Google") << std::endl;
    std::cout << s.detectCapitalUse("falG") << std::endl;
    return 0;
}
