#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
using std::vector;

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int> >& paths) {
        std::vector<std::unordered_set<int> > candidates(N, {1,2,3,4});
        std::vector<std::unordered_set<int> > adjacents(N, std::unordered_set<int>());
        for (const auto& path: paths) {
            adjacents[path[0]-1].insert(path[1]-1);
            adjacents[path[1]-1].insert(path[0]-1);
        }

        std::vector<int> ret(N, 0);
        for (int i=0; i<N; ++i) {
            auto& candidate = candidates[i];
            assert(! candidate.empty());
            ret[i] = *candidate.begin();

            auto& adjacent = adjacents[i];
            for (auto j: adjacent) {
                candidates[j].erase(ret[i]);
            }
        }
        return ret;
    }
};

int main() {
    std::vector<std::vector<int> > paths = {{1,2},{2,3},{3,4},{4,1},{1,3},{2,4}};
    auto ret = Solution().gardenNoAdj(4, paths);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}

