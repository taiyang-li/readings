#include <string> 
#include <iostream>

class Solution {
public:
    std::string gcdOfStrings(const std::string& str1, const std::string& str2) {
        if (str1.empty() || str2.empty()) {
            return std::string();
        }
        return str1.size() > str2.size() ? helper(str1, str2) : helper(str2, str1);
    }

    std::string helper(const std::string& str1, const std::string& str2) {
        std::cout << "str1:" << str1 << " str2:" << str2 << std::endl;
        if (str2.empty()) {
            return str1;
        }
        
        size_t pos = str1.find(str2);
        if (pos == std::string::npos || pos != 0) {
            return std::string();
        }
        
        return str1.size()  > 2 * str2.size() ? helper(str1.substr(str2.size()), str2):
            helper(str2, str1.substr(str2.size()));
    }
};

int main() {
    std::string a = "ababab";
    std::string b = "abab";
    std::cout << Solution().gcdOfStrings(a, b) << std::endl;
}
 
 
