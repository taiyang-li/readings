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
#include <queue>
#include <iostream>
using std::vector;

struct State {
    std::vector<int> seq;
    std::vector<int> ops;
};
class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        int n = A.size();
        std::vector<int> target = A;
        std::sort(target.begin(), target.end());

        std::queue<State> que;
        std::set<std::vector<int> > visited;
        State state;
        state.seq = A;
        state.ops = {};
        que.push(state);
        visited.insert(A);
        while (! que.empty()) {
            auto curr = que.front();
            if (curr.seq == target) {
                return curr.ops;
            }
            que.pop();
            for (auto x: curr.seq) {
                std::cout << x << " ";
            }
            std::cout << std::endl;

            for (int k=1; k<=n; ++k) {
                State next= curr;
                std::reverse(next.seq.begin(), next.seq.begin() + k);
                if (visited.count(next.seq) == 0) {
                    next.ops.push_back(k);
                    que.push(next);
                    visited.insert(next.seq);
                }
            }
        }
        return {};
    }
};

int main() {
    std::vector<int> A = {10,5,1,6,3,8,2,4,7,9};
    auto ret = Solution().pancakeSort(A) ;
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
