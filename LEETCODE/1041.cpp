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
    static const int NORTH = 0;
    static const int EAST = 1;
    static const int SOUTH = 2;
    static const int WEST = 3;

    bool isRobotBounded(const string& instructions) {
        int d = NORTH;
        int x = 0;
        int y = 0;
        for (auto ch: instructions) {
            switch(ch) {
                case 'G': {
                    switch (d) {
                        case NORTH:
                            ++y;
                            break;
                        case EAST:
                            ++x;
                            break;
                        case SOUTH:
                            --y;
                            break;
                        case WEST:
                            --x;
                            break;
                    }
                    break;
                }
                case 'L':
                    d = (d + 3) % 4;
                    break;
                case 'R':
                    d = (d + 1) % 4;
                    break;
            }
        }
        
        if (x == 0 && y == 0) return true;
        if (d == NORTH) return false;
        return true;
    }
};

int main() {
    std::cout << Solution().isRobotBounded("GG") << std::endl;
    std::cout << Solution().isRobotBounded("GGLLGG") << std::endl;
    std::cout << Solution().isRobotBounded("GL") << std::endl;
    return 0;
}

