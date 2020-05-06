#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <stack>
#include <cassert>
using namespace std;

class Solution {
public:
    struct Point {
        int row;
        int col;
    };
    vector<vector<int> > floodFill(vector<vector<int> >& image, int sr, int sc, int newColor) {
        if (image.empty() || image[0].empty() || image[sr][sc] == newColor) {
            return image;
        }

        int old_color = image[sr][sc];
        Point start = {sr, sc};
        dfs(image, start, old_color, newColor);
        return image;
    }

    void dfs(vector<vector<int> >& image, const Point& start, int old_color, int new_color) {
        assert(image[start.row][start.col] == old_color);

        bool have_next = true;
        const int row_num = image.size();
        const int col_num = image[0].size();
        Point next;
        Point curr = start;
        std::stack<Point> st;
        while (have_next) {
            image[curr.row][curr.col] = new_color;
            st.push(curr);

            have_next = false;
            while (! st.empty()) {
                curr = st.top();
                if (curr.row != 0 && image[curr.row-1][curr.col] == old_color) {
                    next.row = curr.row - 1;
                    next.col = curr.col;
                    have_next = true;
                    break;
                }
                if (curr.row != row_num - 1 && image[curr.row+1][curr.col] == old_color) {
                    next.row = curr.row + 1;
                    next.col = curr.col;
                    have_next = true;
                    break;
                }
                if (curr.col != 0 && image[curr.row][curr.col-1] == old_color) {
                    next.row = curr.row;
                    next.col = curr.col - 1;
                    have_next = true;
                    break;
                }
                if (curr.col != col_num - 1 && image[curr.row][curr.col+1] == old_color) {
                    next.row = curr.row;
                    next.col = curr.col + 1;
                    have_next = true;
                    break;
                }
                st.pop();
            }
            curr = next;
        }
    }
};

int main() {
    std::vector<std::vector<int> > image = {{1,1,1},{1,1,0},{1,0,1}};
    auto ret = Solution().floodFill(image, 1, 1, 2);
    for (auto& row : ret) {
        for (auto color : row) {
            std::cout << color << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
