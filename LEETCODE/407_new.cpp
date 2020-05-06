#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#include <queue>
using namespace std;

static const int BLOCK = 1;
static const int HOLLOW = 0;
static const int VISITED_HOLLOW = 2;

struct Cell {
    int row;
    int col;
    int height;
    Cell(int r, int c, int h) : row(r), col(c), height(h) {}
    /*
    bool operator<(const Cell& other) {
        return height > other.height;
    }
    */
    friend bool operator<(const Cell& left, const Cell& right) {
        return left.height > right.height;
    }
};

class Solution {
public:
    inline int trapRainWater(vector<vector<int> >& heightMap) {
        if (heightMap.empty() || heightMap[0].empty()) {
            return 0;
        }

        const int row_num = heightMap.size();
        const int col_num = heightMap[0].size();

        std::priority_queue<Cell> pq;
        std::vector<std::vector<char> > visited(heightMap.size(), std::vector<char>(heightMap[0].size(), 0));
        for (int i=0; i<row_num; ++i) {
            pq.emplace(i, 0, heightMap[i][0]);
            pq.emplace(i, col_num-1, heightMap[i][col_num-1]);
            visited[i][0] = 1;
            visited[i][col_num-1] = 1;
        }
        for (int i=1; i<col_num-1; ++i) {
            pq.emplace(0, i, heightMap[0][i]);
            pq.emplace(row_num-1, i, heightMap[row_num-1][i]);
            visited[0][i] = 1;
            visited[row_num-1][i] = 1;
        }

        int ret = 0;
        const std::vector<std::vector<int> > directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        while (! pq.empty()) {
            Cell cell = pq.top();
            pq.pop();
            for (const auto& direction: directions) {
                int row = cell.row + direction[0];
                int col = cell.col + direction[1];
                if (row < 0 || row >= row_num || col < 0 || col >= col_num || visited[row][col] == 1) {
                    continue;
                }
                if (cell.height > heightMap[row][col]) {
                    ret += cell.height - heightMap[row][col];
                }
                visited[row][col] = 1;
                pq.emplace(row, col, std::max(cell.height, heightMap[row][col]));
            }
        }
        return ret;
    }
};

int main() {
    std::vector<std::vector<int> > height_map = {{1,4,3,1,3,2}, {3,2,1,3,2,4}, {2,3,3,2,3,1}};
    std::cout << Solution().trapRainWater(height_map);
    return 0;
}
