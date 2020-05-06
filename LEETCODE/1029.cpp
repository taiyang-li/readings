#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
using std::vector;
using std::string;


class Solution {
public:
    int twoCitySchedCost(vector<vector<int> >& costs) {
        int sum = 0;
        const int len = costs.size();
        std::vector<int> delta(len, 0);
        for (int i=0; i<len; ++i) {
            sum += costs[i][0];
            delta[i] = costs[i][1] - costs[i][0];
        }

        std::sort(delta.begin(), delta.end());
        for (int i=0; i<len/2; ++i) {
            sum += delta[i];
        }
        return sum;
    }
};
int main() {
    return 0;
}

