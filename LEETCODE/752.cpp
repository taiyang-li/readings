#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <map>
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, const string& target) {
        std::map<std::string, std::string> paths;
        std::set<std::string> deadend_set(deadends.begin(), deadends.end());
        std::set<std::string> visited;
        std::queue<std::string> que;

        int ret = 0;
        const std::string dummy;
        const std::string start = "0000";
        if (deadend_set.count(start) > 0) {
            return -1;
        }
        que.push(start);
        que.push(dummy);
        while (! que.empty()) {
            auto curr = que.front();
            que.pop();
            std::cout << "depth:" << ret << ",curr:" << curr << std::endl;
            if (curr == target) {
                std::string target_path;
                target_path.append(curr);
                auto mit = paths.find(curr);
                while (mit != paths.end()) {
                    target_path = mit->second + " " + target_path;
                    mit = paths.find(mit->second);
                }
                std::cout << "path:" << target_path << std::endl;
                return ret;
            } else if (curr == dummy) {
                ++ret;
                if (! que.empty()) {
                    que.push(dummy);
                }
                continue;
            } else if (deadend_set.count(dummy) > 0) {
                continue;
            } else {
                visited.insert(curr);
            }
            
            auto children = find_children(curr, deadend_set, visited);
            for (const auto& child: children) {
                que.push(child);
                paths[child] = curr;
            }
        }
        return -1;
    }

    std::set<std::string> find_children(const std::string& curr,
            const std::set<std::string>& deadend_set,
            std::set<std::string>& visited) {
        std::set<std::string> ret;
        
        // rotate
        for (int i=0; i<4; ++i) {
            for (auto j: {1, -1}) {
                std::string child(curr);
                char ch = '0' + ((child[i] - '0') + j + 10) % 10;
                child[i] = ch;

                if (deadend_set.count(child) > 0 || visited.count(child) > 0) {
                    continue;
                }
                visited.insert(child);
                ret.insert(child);
            }
        }

        /*
        // swap
        for (int i=0; i<3; ++i) {
            std::string child(curr);
            std::swap(child[i], child[i+1]);

            if (deadend_set.count(child) > 0 || visited.count(child) > 0) {
                continue;
            }
            visited.insert(child);
            ret.insert(child);
        }
        */
        return ret;
    }
};

int main() {
    std::vector<std::string> deadends = {"0201","0101","0102","1212","2002"};
    // std::vector<std::string> deadends = {"0000"};
    std::string target = "0202";
    std::cout << Solution().openLock(deadends, target) << std::endl;
    return 0;
}
