#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <set>
#include <stack>
#include <cassert>
#include <map>
#include <functional>
using namespace std;

struct Cell {
    int row;
    int col;

    Cell(int r=0, int c=0) : row(r), col(c) {}

    Cell& operator=(const Cell& other) {
        row = other.row;
        col = other.col;
        return *this;
    }

    friend Cell operator+(const Cell& lhs, const Cell& rhs) {
        Cell ret(lhs.row + rhs.row, lhs.col + rhs.col);
        return ret;
    }
    
    friend bool operator<(const Cell& lhs, const Cell& rhs) {
        if (lhs.row < rhs.row) {
            return true;
        } else if (lhs.row == rhs.row) {
            return std::less<int>()(lhs.col, rhs.col);
        } else {
            return false;
        }
    }
};

const static std::vector<Cell> directions = {Cell(1, 0), Cell(-1, 0), Cell(0, -1), Cell(0, 1)};

class Solution {
public:
    typedef std::function<void(const Cell& cell, int)> CallBack;

    int largestIsland(std::vector<std::vector<int> >& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        const int row_num = grid.size();
        const int col_num = grid[0].size();
        std::vector<std::vector<char> > visited(row_num, std::vector<char>(col_num, 0));
        std::map<Cell, std::vector<std::pair<int, Cell> > > reverse_indexes;
        for (int row=0; row<row_num; ++row) {
            for (int col=0; col<col_num; ++col) {
                if (visited[row][col] == 0 && grid[row][col] == 1) {
                    int size = 0;
                    std::set<Cell> edge_cells;
                    Cell cell(row, col);
                    CallBack cb = std::bind(&Solution::callback, std::ref(size), std::ref(edge_cells), 
                            std::placeholders::_1, std::placeholders::_2);
                    dfs(cell, grid, visited, cb);
                    // 所有的grid值都为1
                    if (edge_cells.empty()) {
                        return size;
                    }
                    for (const auto& edge_cell: edge_cells) {
                        reverse_indexes[edge_cell].push_back(std::make_pair(size, cell));
                    }
                }
            }
        }

        int ret = 1;
        for (const auto& edge_cell : reverse_indexes) {
            int sum = 1;
            for (const auto& region : edge_cell.second) {
                sum += region.first;
            }
            ret = std::max(ret, sum);
        }
        return ret;
    }

    static void callback(int& size, std::set<Cell>& edge_cells, const Cell& edge_cell, int value) {
        if (value == 1) {
            size += 1;
        } else {
            edge_cells.insert(edge_cell);
        }
    }

    void dfs(const Cell& cell, std::vector<std::vector<int> >& grid,
            std::vector<std::vector<char> >& visited, const CallBack& cb) {
        assert(visited[cell.row][cell.col] == 0 && grid[cell.row][cell.col] == 1);
        const int row_num = grid.size();
        const int col_num = grid[0].size();
        bool have_next = true;
        Cell curr = cell;
        Cell next;
        std::stack<Cell> st;
        while (have_next) {
            visited[curr.row][curr.col] = 1;
            cb(curr, grid[curr.row][curr.col]);
            st.push(curr);

            have_next = false;
            while (! st.empty()) {
                curr = st.top();
                for (const auto& direction: directions) {
                    next = curr + direction;
                    if (next.row < 0 || next.row >= row_num || next.col < 0 || next.col >= col_num) {
                        continue;
                    }
                    if (grid[next.row][next.col] == 0) {
                        cb(next, grid[next.row][next.col]);
                    } else if (visited[next.row][next.col] == 0) {
                        have_next = true;
                        break;
                    } 
                }
                if (have_next) {
                    break;
                } else {
                    st.pop();
                }
            }
            curr = next;
        }
    }
};

int main() {
    vector<vector<int> > grid = {{0, 0}, {0, 0}};
    std::cout << Solution().largestIsland(grid) << std::endl;
    return 0;
}
