#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

class Solution {
public:
    bool checkValidString(const std::string& s) {
        if (s.empty()) {
            return true;
        }

        int upper = 0;
        int lower = 0;
        for (auto ch : s) {
            if (ch == '(') {
                upper++;
                lower++;
            } else if (ch == ')') {
                upper--;
                lower--;
            } else {
                upper++;
                lower--;
            }
            if (upper < 0) {
                return false;
            }
            lower = std::max(lower, 0);
        }
        return lower == 0;
    }
};

int main() {
    /*
    std::cout << Solution().checkValidString("()") << std::endl;
    std::cout << Solution().checkValidString("(*)") << std::endl;
    */
    std::cout << Solution().checkValidString("(())((())()()(*)(*()(())())())()()((()())((()))(*") << std::endl;
    return 0;
}
