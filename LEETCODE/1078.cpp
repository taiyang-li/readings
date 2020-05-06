#include <string> 
#include <iostream>
#include <vector>
using std::vector;
using std::string;

class Solution {
public:
    vector<string> findOcurrences(const string& text, const string& first, const string& second) {
        std::string target(first);
        target += ' ';
        target += second;

        std::vector<std::string> ret;
        size_t pos = text.find(target);
        while (pos != std::string::npos) {
            size_t start = text.find_first_not_of(' ', pos + target.size());
            if (start == std::string::npos) {
                break;
            }
            
            size_t end = text.find_first_of(' ', start);
            if (end == std::string::npos) {
                end = text.size();
            }
            ret.push_back(text.substr(start, end-start));
            pos = text.find(target, pos + target.size());
        }
        return ret;
    }
};

int main() {
    std::string text = "alice is a good girl she is a good student";
    std::string first = "a";
    std::string second = "good";
    auto ret = Solution().findOcurrences(text, first, second);
    for (const auto& x : ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
 
 
