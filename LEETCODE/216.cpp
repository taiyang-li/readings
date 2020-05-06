#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <stack>
using namespace std;

class Solution {
public:
    vector<vector<int> > combinationSum3(int k, int n) {
        return dfs(k, n);
    }

    vector<vector<int> > dfs(int k, int n) {
        vector<vector<int> > ret;
        std::vector<int> path = {1};
        int sum = 1;
        int curr = 0;
        int next = 0;
        int waterline = 0;
        while (! path.empty()) {
            /*
            for (auto x: path) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            */

            if (int(path.size()) == k && sum == n) {
                ret.push_back(path);
            }

            waterline = path.back();
            while (1) {
                curr = path.back();
                do {
                    next = 0;

                    // 剪枝1：数字已经填满，或者可取数字的数量小于未填数字的数量，提前跳出
                    int left_k = k - int(path.size());
                    if (left_k <= 0 || 9 - waterline < left_k) {
                        break;
                    } 

                    // 剪枝2：未填数字之和的最大值都小于 n - sum 或 其最小值大于n - sum
                    int left_n = n - sum;
                    int max_n = left_k * (9 + 9 - left_k + 1) / 2;
                    int min_n = left_k * (waterline + 1 + waterline + 1 + left_k - 1) / 2;
                    if (max_n < left_n || min_n > left_n) {
                        break;
                    }

                    next = waterline + 1;
                } while (0);
                
                if (next != 0) {
                    path.push_back(next);
                    sum += next;
                    break;
                } 

                if (path.empty()) {
                    break;
                }

                sum -= curr;
                path.pop_back();
                waterline = curr;
            }
        }
        return ret;
    }
};

int main() {
    auto ret = Solution().combinationSum3(3, 9);
    for (const auto& x: ret) {
        for (auto y: x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
