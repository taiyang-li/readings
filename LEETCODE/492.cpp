#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        std::vector<int> ret(2, 0);
        int sq = std::sqrt(area);
        for (int i=sq; i>=1; --i) {
            if (area % i == 0) {
                ret[0] = area/i;
                ret[1] = i;
                return ret;
            }
        }
        // impossible
        return ret;
    }
};

int main() {
    return 0;
}

