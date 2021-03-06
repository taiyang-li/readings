#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
        auto indegree = gen_indegree(numCourses, prerequisites);
        auto adjacent_table = gen_adjacent_table(numCourses, prerequisites);

        std::vector<int> ret;
        ret.reserve(numCourses);
        std::queue<int> q;
        for (int i=0; i<numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        // 宽度优先遍历
        while (! q.empty()) {
            int curr = q.front();
            ret.push_back(curr);
            q.pop();

            for (auto next : adjacent_table[curr]) {
                if (indegree[next] > 0) {
                    if (--indegree[next] == 0) {
                        q.push(next);
                    }
                }
            }
        }
        if (int(ret.size()) == numCourses) {
            return ret;
        } else {
            return std::vector<int>();
        }
    }

    inline std::vector<int> gen_indegree(int numCourses, std::vector<std::pair<int, int> >& prerequisites) {
        std::vector<int> ret(numCourses, 0);
        for (const auto& prerequisite : prerequisites) {
            ret[prerequisite.first]++;
        }
        return ret;
    }

    inline std::vector<std::set<int> > gen_adjacent_table(int numCourses, std::vector<std::pair<int, int> >& prerequisites) {
        std::vector<std::set<int> > ret(numCourses);
        for (const auto& prerequisite : prerequisites) {
            ret[prerequisite.second].insert(prerequisite.first);
        }
        return ret;
    }
};

int main() {
    std::vector<std::pair<int, int> > prerequisites = {{1,0},{2,0},{3,1},{3,2}};
    auto ret = Solution().findOrder(4, prerequisites);
    for (auto x : ret) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
