#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <sstream>
#include <functional>
#include <cstdint>
#include <random>
#include <queue>
#include <algorithm>
using std::vector;

class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        std::vector<int> abc;
        abc.push_back(a);
        abc.push_back(b);
        abc.push_back(c);
        std::sort(abc.begin(), abc.end());
        if (abc[2] - abc[0] == 2) {
            return {0,0};
        }

        int max_moves = abc[1] - abc[0] - 1 + abc[2] - abc[1] - 1;
        int min_moves = (abc[1] - abc[0] <= 2 || abc[2] - abc[1] <= 2) ? 1 : 2;
        return {min_moves, max_moves};
    }
};

int main() {
    return 0;
}
