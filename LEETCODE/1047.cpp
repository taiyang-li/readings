#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <cstring>

class Solution {
public:
    std::string removeDuplicates(const std::string& S) {
        char* buf[2];
        int in_use = 0;
        int len = S.size();
        if (len <= 1) return S;
        buf[0] = new char[len+1];
        buf[1] = new char[len+1];
        ::strncpy(buf[0], S.c_str(), len+1);

        while (1) {
            // std::cout << buf[in_use] << std::endl;
            char* curr = buf[in_use];
            if (curr[0] == 0 || curr[1] == 0) {
                break;
            }
            char* prev = curr;
            ++curr;
            int pos = 0;
            while (1) {
                while (*curr == *prev) {
                    ++curr;
                }
                if ((curr - prev) % 2 == 1) {
                    buf[1-in_use][pos++] = *prev;
                }

                if (*curr == 0) {
                    break;
                }
                prev = curr;
                ++curr;
            }
            buf[1-in_use][pos] = 0;
            if (pos >= curr - buf[in_use]) {
                break;
            }
            in_use = 1 - in_use;
        }

        std::string ret(buf[in_use]);
        delete [] buf[0];
        delete [] buf[1];
        return ret;
    }
};

int main() {
    std::cout << Solution().removeDuplicates("abbaca") << std::endl;
    return 0;
}
