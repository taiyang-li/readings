#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    int numberOfBoomerangs(vector<vector<int> >& points) {
        const int N = points.size();
        if (N <= 2) return 0;
        std::vector<std::vector<int> > d(N, std::vector<int>(N, 0));
        for (int i=0; i<N; ++i) {
            for (int j=i+1; j<N; ++j) {
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                d[i][j] = d[j][i] = dx * dx + dy * dy;
            }
        }
        
        int ret = 0;
        for (int i=0; i<N; ++i) {
            std::vector<int> tmp = d[i];
            std::sort(tmp.begin(), tmp.end());
            int prev = 0;
            int count = 0;
            for (int j=1; j<N; ++j) {
                if (tmp[j] != prev) {
                    if (count >= 2) {
                        ret += count * (count-1);
                    }
                    count = 1;
                } else {
                    ++count;
                }
                prev = tmp[j];
            }
            if (count >= 2) {
                ret += count * (count-1);
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

