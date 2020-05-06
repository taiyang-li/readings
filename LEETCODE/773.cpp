#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int slidingPuzzle(vector<vector<int> >& board) {
        int start = encode_board(board);
        int target = encode_board(Solution::_target_board);
        int depth = 0;
        std::set<int> visited;
        std::queue<int> que;
        que.push(start);
        que.push(0);
        while (! que.empty()) {
            int curr = que.front();
            // std::cout << curr << std::endl;
            visited.insert(curr);
            que.pop();
            if (curr == target) {
                return depth;
            } else if (curr == 0) {
                ++depth;
                if (! que.empty()) {
                    que.push(0);
                }
                continue;
            }

            auto tmp = decode_board(curr);
            int row = 0;
            int col = 0;
            bool found = false;
            for (row = 0; row < 2; ++row) {
                for (col = 0; col < 3; ++col) {
                    if (tmp[row][col] == 0) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }

            for (const auto& direction: Solution::_directions) {
                if (row + direction.first >=0 && row + direction.first < 2 &&
                        col + direction.second >=0 && col + direction.second < 3) {
                    std::swap(tmp[row][col], tmp[row + direction.first][col + direction.second]);
                    int next = encode_board(tmp);
                    if (visited.count(next) == 0) {
                        que.push(next);
                        // std::cout << "children: " << next << std::endl;
                    }
                    std::swap(tmp[row][col], tmp[row + direction.first][col + direction.second]);
                }
            }
        }
        return -1;
    }
protected:
    static const std::vector<std::vector<int> > _target_board;
    static const std::vector<std::pair<int, int> > _directions;
    
    static int encode_board(const std::vector<std::vector<int> >& board) {
        int ret = 0;
        for (const auto& row: board) {
            for (auto val: row) {
                // std::cout << val << std::endl;
                ret = 10 * ret + val;
            }
        }
        return ret;
    }

    static std::vector<std::vector<int> > decode_board(int code) {
        std::vector<std::vector<int> > ret(2, std::vector<int>(3, 0));
        for (int row=1; row>=0; --row) {
            for (int col=2; col>=0; --col) {
                ret[row][col] = code % 10;
                code /= 10;
            }
        }
        return ret;
    }
};

const std::vector<std::vector<int> > Solution::_target_board = {{1, 2, 3}, {4, 5, 0}};
const std::vector<std::pair<int, int> > Solution::_directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
    // std::vector<std::vector<int> > board = {{1, 2, 3}, {4, 0, 5}};
    std::vector<std::vector<int> > board = {{1, 2, 3}, {5, 4, 0}};
    std::cout << Solution().slidingPuzzle(board) << std::endl;
    return 0;
}
