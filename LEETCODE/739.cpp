#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ret(temperatures.size(), 0);
        stack<size_t> s;
        for (size_t i=0; i<temperatures.size(); ++i) {
            while (! s.empty() && temperatures[i] > temperatures[s.top()]) {
                ret[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return ret;
    }
};

int main () {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution solution;
    vector<int> ret = solution.dailyTemperatures(temperatures);
    for_each(ret.begin(), ret.end(), [](int i) -> void {std::cout << i << std::endl;});
    return 0;
}
