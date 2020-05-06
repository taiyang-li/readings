#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class VectorHash {
public:
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

class Solution {
public:
    static const int NORTH = 0;
    static const int EAST = 1;
    static const int SOUTH = 2;
    static const int WEST = 3;
    int robotSim(vector<int>& commands, vector<vector<int> >& obstacles) {
        _x = 0;
        _y = 0;
        _d = NORTH;
        _max_dsquare = 0;
        _obstacles.clear();
        for (const auto& obstacle: obstacles) {
            _obstacles.insert(obstacle);
        }
        
        for (auto cmd: commands) {
            run_command(cmd);
        }
        return _max_dsquare;
    }
    
    void run_command(int cmd) {
        switch(cmd) {
            case -1:
                _d = (_d + 1)%4;
                break;
            case -2:
                _d = (_d + 3)%4;
                break;
            default: 
                forwarding(cmd);
                break;
        }
    }
    
    void forwarding(int steps) {
        int dx = 0;
        int dy = 0;
        switch(_d) {
            case NORTH: dy = 1; break;
            case EAST: dx = 1; break;
            case SOUTH: dy = -1; break;
            case WEST: dx = -1; break;
        }
        for (int i=0; i<steps; ++i) {
            _x += dx;
            _y += dy;
            std::vector<int> next = {_x, _y};
            if (_obstacles.count(next) > 0) {
                _x -= dx;
                _y -= dy;
                break;
            }
        }
        _max_dsquare = std::max(_max_dsquare, _x*_x + _y*_y);
    }

private:
    int _x;
    int _y;
    int _d;
    int _max_dsquare;
    std::unordered_set<std::vector<int>, VectorHash> _obstacles;
};

int main() {
    return 0;
}

