#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>

using namespace std;


class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int prev = -1;
        int ret = 0;
        int candidate = 0;
        for (size_t i=0; i<seats.size(); ++i) {
            if (seats[i] == 1) {
                candidate = (prev == -1) ? i : (i-prev)/2;
                if (candidate > ret) {
                    ret = candidate;
                }
                prev = i;
            }
        }
        if (int(seats.size()) - prev - 1 > ret) {
            ret = seats.size() - prev - 1;
        }
        return ret;
    }
};

int main () {
    Solution solution;
    vector<int> seats = {1,0,0,0,1,0,1};
    std::cout << solution.maxDistToClosest(seats) << std::endl;
    return 0;
}
