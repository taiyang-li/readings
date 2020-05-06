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
using std::vector;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        int n = A.size();
        std::vector<int> target = A;
        std::sort(target.begin(), target.end());

        std::vector<int> curr = A;
        if (curr == target) {
            return {};
        }

        std::set<std::vector<int> > visited;
        std::stack<std::vector<int> > st;
        std::vector<int> next;
        bool have_next = true;
        int k = 0;
        std::vector<int> ret;
        while (have_next) {
            visited.insert(curr);
            st.push(curr);
            if (k != 0) {
                ret.push_back(k);
            }
            if (curr == target) {
                return ret;
            }
            
            have_next = false;
            while (! st.empty()) {
                curr = st.top();
                for (k=1; k<=n; ++k) {
                    next = curr;
                    std::reverse(next.begin(), next.begin() + k);
                    if (visited.count(next) == 0) {
                        have_next = true;
                        break;
                    }
                }

                if (have_next) {
                    break;
                } else {
                    st.pop();
                    ret.pop_back();
                }
            }
            curr = next;
        }
        return ret;
    }
};

int main() {
    std::vector<int> A = {3,2,4,1};
    auto ret = Solution().pancakeSort(A) ;
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
