#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <bitset>
#include <cassert>
#include <stack>
using namespace std;


class Solution {
public:
    int findCircleNum(vector<vector<int> >& M) {
        const int students = M.size();
        if (students <= 1) {
            return students;
        }

        int ret = 0;
        std::vector<char> visited(students, 0);
        for (int i=0; i<students; ++i) {
            if (visited[i] != 0) {
                continue;
            }
            dfs(M, i, visited);
            ret++;
        }
        return ret;
    }

    void dfs(vector<vector<int> >& M, int i, std::vector<char>& visited) {
        assert(visited[i] == 0);
        int curr = i;
        int next = 0;
        const int len = visited.size();
        std::stack<int> st;
        while (curr != len) {
            visited[curr] = 1;
            st.push(curr);
            
            while (! st.empty()) {
                curr = st.top();
                for (next=0; next<len; ++next) {
                    if (M[curr][next] == 1 && visited[next] == 0) {
                        break;
                    }
                }
                if (next != len) {
                    break;
                }
                st.pop();
            }
            curr = next;
        }
    }
};

int main() {
    // std::vector<std::vector<int> > M = {{1,1,0}, {1,1,0}, {0,0,1}};
    std::vector<std::vector<int> > M = {{1,1,0}, {1,1,1}, {0,1,1}};
    std::cout << Solution().findCircleNum(M) << std::endl;
    return 0;
}
