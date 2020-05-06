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

        int count = 0;
        return helper(s, count, 0);
    }

    bool helper(const std::string& s, int& count, int i) {
        while (i < int(s.size()) && s[i] != '*') {
            if (s[i] == '(') {
                count++;
            } else if (s[i] == ')') {
                if (count == 0) {
                    return false;
                } else {
                    count--;
                }
            } 
            i++;
        }
        if (i == int(s.size())) {
            return count == 0;
        }

        int count1 = count;
        int count2 = count + 1;
        bool ret = helper(s, count1, i+1) || helper(s, count2, i+1);
        if (count > 0) {
            int count2 = count - 1;
            ret = ret || helper(s, count2, i+1);
        }
        return ret;
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
