#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
using std::vector;
using std::string;

class Solution {
public:
    bool isBoomerang(vector<vector<int> >& points) {
        if (points[0] == points[1] || points[1] == points[2] || points[2] == points[0]) {
            return false;
        }

        int dx1 = points[1][0] - points[0][0];
        int dx2 = points[2][0] - points[0][0];
        if (dx1 == 0 || dx2 == 0) {
            return ! (dx1 == dx2);
        }

        int dy1 = points[1][1] - points[0][1];
        int dy2 = points[2][1] - points[0][1];
        return !(dx2 * dy1 == dx1 * dy2);
    }
};

int main() {
    std::vector<std::vector<int> > a = {{1,1}, {3,2}, {2,3}};
    std::cout << Solution().isBoomerang(a) << std::endl;
    return 0;
}

