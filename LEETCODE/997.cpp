#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        if (N == 1) return 1;

        std::map<int, int> trust_map;
        std::map<int, std::vector<int> > reverse_trust_map;
        for (const auto& x: trust) {
            trust_map[x[0]] = x[1];
            reverse_trust_map[x[1]].push_back(x[0]);
        }

        for (const auto& x: reverse_trust_map) {
            if (int(x.second.size()) != N - 1) {
                continue;
            }

            if (trust_map.count(x.first) > 0) {
                continue;
            }
            
            return x.first;
        }
        return -1;
    }
}; 
int main() {
    int N = 3;
    std::vector<std::vector<int> >  trust = {{1,3},{2,3}};
    std::cout << Solution().findJudge(N, trust) << std::endl;
    return 0;
}
