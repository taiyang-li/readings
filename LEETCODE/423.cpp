#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <map>
using std::vector;
using std::string;

class Solution {
public:
    string originalDigits(const string& s) {
        int count[128] = {0};
        for (auto ch: s) {
            count[int(ch)]++;
        }
        std::vector<int> num(10, 0);
        num[0] = count['z'];
        num[2] = count['w'];
        num[4] = count['u'];
        num[6] = count['x'];
        num[8] = count['g'];
        num[5] = count['f'] - num[4];
        num[3] = count['h'] - num[8];
        num[1] = count['o'] - num[0] - num[2] - num[4];
        num[7] = count['v'] - num[5];
        num[9] = count['i'] - num[5] - num[6] - num[8];

        std::string ret;
        for (int i=0; i<10; ++i) {
            if (num[i] == 0) {
                continue;
            }
            ret += std::string(num[i], '0' + i);
        }
        return ret;
    }
};

int main() {
    std::string s = "owoztneoer";
    std::cout << Solution().originalDigits(s) << std::endl;
    return 0;
}
