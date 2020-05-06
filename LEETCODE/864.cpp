#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <cctype>
#include <sstream>
using namespace std;

struct State {
    int row;
    int col;
    char keys[6];

    State(int r=0, int c=0, const char* k=NULL): row(r), col(c) {
        if (k == NULL) {
            ::memset(keys, 0, 6 * sizeof(char));
        } else {
            ::memcpy(keys, k, 6 * sizeof(char));
        }
    }

    State(const State& other): row(other.row), col(other.col) {
        ::memcpy(keys, other.keys, 6 * sizeof(char));
    }

    bool operator<(const State& other) const {
        return row < other.row || row == other.row && col < other.col || 
            row == other.row && col == other.col && 
            ::memcmp(keys, other.keys, 6 * sizeof(char)) < 0;
    }
    
    inline uint64_t encode() const {
        uint64_t ret = 0;
        ret = ((uint64_t)row << 48) | ((uint64_t)col << 32);
        for (int i=0; i<6; ++i) {
            if (keys[i] != 0) {
                ret |= (uint64_t)1 << i;
            }
        }
        return ret;
    }

    inline std::string to_string() const {
        std::ostringstream oss;
        oss << "row:" << row << ",col:" << col << ",key:";
        bool first = true;
        for (int i=0; i<6; ++i) {
            if (keys[i] != 0) {
                if (first) {
                    oss << char('a' + i);
                    first = false;
                } else {
                    oss << "|" << char('a' + i);
                }
            }
        }
        return oss.str();
    }
};

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        _row_num = grid.size();
        if (_row_num == 0) return -1;
        _col_num = grid[0].size();
        if (_col_num == 0) return -1;

        _start_row = 0;
        _start_col = 0;
        ::memset(_total_keys, 0, 6 * sizeof(char));
        for (int i=0; i<_row_num; ++i) {
            for (int j=0; j<_col_num; ++j) {
                char ch = grid[i][j];
                if (ch >= 'a' && ch <= 'f') {
                    _total_keys[ch - 'a'] = 1;
                } else if (ch == '@') {
                    _start_row = i;
                    _start_col = j;
                }
            }
        }

        int ret = 0;
        const State dummy(-1, -1);
        std::set<uint64_t> visited;
        std::queue<State> q;
        q.push(State(_start_row, _start_col));
        q.push(dummy);
        while (! q.empty()) {
            auto curr = q.front();
            /*
            std::cout << "depth:" << ret << "," << curr.to_string() 
                << ",sign:" << curr.encode() << ",visited:";
            for (auto sign: visited) {
                std::cout << sign << "|";
            }
            std::cout << std::endl;
            */

            q.pop();
            if (isSuccess(curr)) {
                return ret;
            } else if (curr.row < 0 || curr.col < 0) {
                ++ret;
                if (! q.empty()) {
                    q.push(dummy);
                }
                continue;
            }

            visited.insert(curr.encode());
            auto children = find_children(curr, grid, visited);
            for (const auto& child: children) {
                q.push(child);
                visited.insert(child.encode());
            }
        }
        return -1;
    }

    std::vector<State> find_children(const State& state, 
            const vector<string>& grid, std::set<uint64_t>& visited) {
        std::vector<State> ret;
        for (const auto& direction: Solution::_directions) {
            int new_row = state.row + direction.first;
            int new_col = state.col + direction.second;
            if (new_row < 0 || new_row >= _row_num || 
                    new_col < 0 || new_col >= _col_num) {
                continue;
            }

            char ch = grid[new_row][new_col];
            if (ch == '#' || (ch >= 'A' && ch <= 'F' && 
                        state.keys[::tolower(ch) - 'a'] == 0)) {
                continue;
            }

            State child(new_row, new_col, state.keys);
            if (ch >= 'a' && ch <= 'f') {
                child.keys[ch - 'a'] = 1;
            }
            if (visited.find(child.encode()) != visited.end()) {
                continue;
            }

            ret.push_back(child);
        }
        return ret;
    }

    bool isSuccess(const State& state) {
        return ::memcmp(state.keys, _total_keys, 6 * sizeof(char)) == 0;
    }

protected:
    char _total_keys[6];
    int _start_row;
    int _start_col;
    int _row_num;
    int _col_num;
    static const std::vector<std::pair<int, int> > _directions;
};

const std::vector<std::pair<int, int> > Solution::_directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    // std::vector<std::string> grid = {"@.a.#","###.#","b.A.B"};
    // std::vector<std::string> grid = {"@..aA","..B#.","....b"};
    std::vector<std::string> grid = {
        ".#......###..#.",
        ".###C..#...b...",
        "..#..#.........",
        ".........#.....",
        ".....@#.#......",
        "#.##...#..##...",
        "..d#...a...#...",
        "..###..........",
        "........#....#.",
        "..#.#..#...c#.#",
        "D#..........#.#",
        "............#A.",
        "..#..##...#....",
        "#...#..#..B....",
        ".....##.....#.."
    };
    std::cout << Solution().shortestPathAllKeys(grid) << std::endl;
    return 0;
}
