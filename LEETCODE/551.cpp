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
    bool checkRecord(const string& s) {
        int Ls = 0;
        int As = 0;
        char prev = -1;
        for (auto ch: s) {
            if (ch == 'A') {
                As++;
            } else if (ch == 'L') {
                if (prev == ch) {
                    Ls++;
                } else if (Ls < 2){
                    Ls = 0;
                }
            }
            prev = ch;
        }
        return Ls < 2 && As <= 1;
    }
};

int main() {
    std::string s = "PPALLP";
    std::cout << Solution().checkRecord(s) << std::endl;
    s = "PPALLL";
    std::cout << Solution().checkRecord(s) << std::endl;
    return 0;
}
