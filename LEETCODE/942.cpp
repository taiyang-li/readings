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
using std::string;

typedef std::vector<int> State;

class Solution {
public:
    vector<int> diStringMatch(const string& S) {
        int len = S.size();
        const int N = len + 1;
        std::set<State> visited;
        for (int i=0; i<N; ++i) {
            auto tmp = dfs(i, S, visited);
            if (! tmp.empty()) {
                return tmp;
            }
        }
        return std::vector<int>();
    }

    vector<int> dfs(int start, const string& S, std::set<State>& visited) {
        const int N = S.size() + 1;

        State curr;
        State next;
        curr.push_back(start);
        std::stack<State> st;
        bool has_next = true;
        while (has_next) {
            visited.insert(curr);
            st.push(curr);
            if (int(curr.size()) == N) {
                return curr;
            }

            /*
            for (auto x: curr) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            */

            has_next = false;
            while (! st.empty()) {
                curr = st.top();
                // find next
                for (int i=0; i<N; ++i) {
                    if (std::find(curr.begin(), curr.end(), i) != curr.end()) {
                        continue;
                    }

                    if (i > curr.back() && S[curr.size() - 1] == 'D') {
                        continue;
                    }

                    if (i < curr.back() && S[curr.size() - 1] == 'I') {
                        continue;
                    }

                    next = curr;
                    next.push_back(i);
                    if (visited.count(next) > 0) {
                        continue;
                    }
                    has_next = true;
                    break;
                }

                if (has_next) {
                    break;
                }
                st.pop();
            }
            curr = next;
        }
        return std::vector<int>();
    }
}; 
int main() {
    std::string S = "IDID";
    auto ret = Solution().diStringMatch(S);
    /*
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    */
    return 0;
}
