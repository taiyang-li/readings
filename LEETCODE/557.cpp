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
    string reverseWords(const string& s) {
        std::string ret(s);
        size_t curr = 0;
        size_t begin = 0;
        size_t end = 0;
        while (1) {
            begin = ret.find_first_not_of(' ', curr);
            if (begin == std::string::npos) {
                break;
            }
            end = ret.find_first_of(' ', begin);
            std::reverse(ret.begin() + begin, end == std::string::npos ? ret.end() : ret.begin() + end);
            curr = end;
        }
        return ret;
    }
};

int main() {
    std::string s = "Let's take LeetCode contest";
    std::cout << Solution().reverseWords(s) << std::endl;
}
