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
    int binaryGap(int N) {
        int last1_index = -1;
        int index = 0;
        char prev = -1;
        char curr = 0;
        int ret = 0;
        while (N > 0) {
            curr = N % 2;
            if (last1_index >= 0) {
                ret = std::max(ret, index - last1_index);
            }

            if (curr == 1) {
                last1_index = index;
            }
            prev = curr;
            ++index;
            N /= 2;
        }
        return ret;
    }
};

int main() {
    std::cout << Solution().binaryGap(8) << std::endl;
    return 0;
}
