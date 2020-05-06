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

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        int x11 = rec1[0];
        int y11 = rec1[1];
        int x12 = rec1[2];
        int y12 = rec1[3];
        int x21 = rec2[0];
        int y21 = rec2[1];
        int x22 = rec2[2];
        int y22 = rec2[3];
        if (x21 >= x12 || x22 <= x11 || y21 >= y12 || y22 <= y11) {
            return false;
        }
        return true;
    }
};

int main() {
    return 0;
}

