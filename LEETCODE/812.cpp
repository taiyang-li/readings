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
    double largestTriangleArea(vector<vector<int> >& points) {
        const int len = points.size();
        double max_area = 0.0;
        for (int i=0; i<len; ++i) {
            for (int j=i+1; j<len; ++j) {
                for (int k=j+1; k<len; ++k) {
                    double a = distance(points[i], points[j]);
                    double b = distance(points[j], points[k]);
                    double c = distance(points[k], points[i]);
                    double L = 0.5 * (a+b+c);
                    max_area = std::max(max_area, std::sqrt(L * (L-a) * (L-b) * (L-c)));
                }
            }
        }
        return max_area;
    }

    double distance(vector<int>& p1, vector<int>& p2) {
        double dx = p1[0] - p2[0];
        double dy = p1[1] - p2[1];
        return std::sqrt(dx*dx+dy*dy);
    }

};

int main() {
    return 0;
}

