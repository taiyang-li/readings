#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
using std::vector;

class Solution {
public:
    vector<vector<int> > kClosest(vector<vector<int> >& points, int K) {
        int low = 0;
        int high = points.size() - 1;
        while (low < high) {
            int pos = partition(points, low, high);
            if (pos == K) {
                return std::vector<std::vector<int> >(points.begin(), points.begin() + K);
            }
            
            if (pos < K) {
                low = pos + 1;
            } else {
                high = pos - 1;
            }
        }
        return std::vector<std::vector<int> >(points.begin(), points.begin() + K);
    }

    int partition(std::vector<std::vector<int> >& points, int low, int high) {
        std::vector<int> pivot = points[low];
        while (low < high) {
            while (low < high && compare(points[high], pivot) >= 0) {
                high--;
            }
            points[low] = points[high];
            
            while (low < high && compare(pivot, points[low]) >= 0) {
                low++;
            }
            points[high] = points[low];
        }
        points[low] = pivot;
        return low;
    }

    int compare(std::vector<int>& lhs, std::vector<int>& rhs) {
        return lhs[0] * lhs[0] + lhs[1] * lhs[1] - (rhs[0] * rhs[0] + rhs[1] * rhs[1]);
    }
};
int main() {
    std::vector<std::vector<int> > points = {{3,3}, {5, -1}, {-2, 4}};
    int K = 2;
    auto ret = Solution().kClosest(points, K);
    for (const auto& x: ret) {
        std::cout << x[0] << " " << x[1] << std::endl;
    }
    return 0;
}
