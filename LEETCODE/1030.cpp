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
    vector<vector<int> > allCellsDistOrder(int R, int C, int r0, int c0) {
        std::vector<std::vector<int> > ret(R*C, {0,0});
        int idx = 0;
        // std::cout << r0 << " " << r0 << std::endl;
        ret[idx++] = {r0, c0};
        int max_dr = std::max(r0, R-1-r0);
        int max_dc = std::max(c0, C-1-c0);
        for (int d=1; d<=max_dr+max_dc; ++d) {
            int lower_dr = std::max(0, d-max_dc);
            int higher_dr = std::min(d, max_dr);
            for (int dr=lower_dr; dr<=higher_dr; ++dr) {
                int dc = d - dr;
                std::unordered_set<int> rs = {r0-dr, r0+dr};
                std::unordered_set<int> cs = {c0-dc, c0+dc};
                for (auto r: rs) {
                    for (auto c: cs) {
                        if (r >= 0 && r <= R-1 && c >=0 && c <= C-1) {
                            // std::cout << r << " " << c << std::endl;
                            ret[idx++] = {r, c};
                        }
                    }
                }
            }
        }
        return ret;
    }
};

int main() {
    auto ret = Solution().allCellsDistOrder(1,2,0,0) ;
    for (const auto& cell : ret) {
        std::cout << cell[0] << " " << cell[1] << std::endl;
    }
    return 0;
}

