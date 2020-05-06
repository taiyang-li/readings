#include <iostream>

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx > sx && ty > sy) {
            if (tx > ty) {
                tx = tx % ty;
            } else {
                ty = ty % tx;
            }
        }
        if (tx == sx) {
            return (ty - sy) % sx == 0;
        }
        if (ty == sy) {
            return (tx - sx) % sy == 0;
        }
        return false;
    }
};

int main() {
    Solution solution;
    std::cout << solution.reachingPoints(6, 5, 11, 16) << std::endl;
    return 0;
}
