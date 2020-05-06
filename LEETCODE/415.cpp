#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Solution {
public:
    std::string addStrings(const std::string& num1, const std::string& num2) {
        const int len = 1 + std::max(num1.size(), num2.size());
        std::string left = std::string(len-num1.size(), '0');
        left.append(num1);
        std::string right = std::string(len-num2.size(), '0');
        right.append(num2);

        char flag = 0;
        char tmp = 0;
        std::string ret(len, '0');
        for (auto i=len-1; i>=0; --i) {
            tmp = (left[i] - '0') + (right[i] - '0') + flag;
            ret[i] = tmp%10 + '0';
            flag = tmp/10;
        }
        return ret[0] == '0' ? ret.substr(1) : ret;
    }
};

int main() {
    std::string num1 = "556233939393023750373";
    std::string num2 = "32930602160342342556";
    std::cout << Solution().addStrings(num1, num2) << std::endl;
    return 0;
}
