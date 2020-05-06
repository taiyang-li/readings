#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <set>
using std::vector;

class Solution {
public:
    /*
    bool canVisitAllRooms(vector<vector<int> >& rooms) {
        std::set<int> curr_keys;
        int n = rooms.size();
        int next = 0;
        int begin = 0;
        int end = (begin + 1) % n;
        curr_keys.insert(rooms[0].begin(), rooms[0].end());
        while (begin != end) {
            next = end;
            if (curr_keys.count(next) > 0) {
                curr_keys.insert(rooms[next].begin(), rooms[next].end());
                end = (end + 1 ) % n;
                std::cout << next << std::endl;
                continue;
            }

            next = (begin - 1 + n) % n;
            if (curr_keys.count(next) > 0) {
                curr_keys.insert(rooms[next].begin(), rooms[next].end());
                begin = next;
                std::cout << next << std::endl;
                continue;
            }
            return false;
        }
        return true;
    }
    */
    bool canVisitAllRooms(vector<vector<int> >& rooms) {
        _visited.clear();
        dfs(rooms, 0);
        return _visited.size() == rooms.size();
    }

    void dfs(std::vector<std::vector<int> >& rooms, int pos) {
        _visited.insert(pos);
        for (auto x: rooms[pos]) {
            if (_visited.count(x) == 0) {
                dfs(rooms, x);
            }
        }
    }

protected:
    std::set<int> _visited;
};

int main() {
    std::vector<std::vector<int> > rooms = {{6,7,8},{5,4,9},{},{8},{4},{},{1,9,2,3},{7},{6,5},{2,3,1}};
    std::cout << Solution().canVisitAllRooms(rooms) << std::endl;
    return 0;
}
