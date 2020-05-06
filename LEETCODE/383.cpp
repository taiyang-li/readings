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
    bool canConstruct(const string& ransomNote, const string& magazine) {
        int mtable[128] = {0};
        for (auto ch : magazine) {
            mtable[int(ch)]++;
        }

        int rtable[128] = {0};
        for (auto ch: ransomNote) {
            rtable[int(ch)]++;
        }

        for (int i=0; i<128; ++i) {
            if (rtable[i] > mtable[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    std::cout << s.canConstruct("a", "b") << std::endl;
    std::cout << s.canConstruct("aa", "ab") << std::endl;
    std::cout << s.canConstruct("aa", "aab") << std::endl;
    return 0;
}

