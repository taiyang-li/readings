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
    int calPoints(vector<string>& ops) {
        std::vector<int> valid_points;
        int ret = 0;
        for (const auto& op : ops) {
            if (op == "C") {
                if (valid_points.empty()) {
                    return -1;
                }
                ret -= *(valid_points.rbegin());
                valid_points.pop_back();
            } else if (op == "D") {
                if (valid_points.empty()) {
                    return -1;
                }
                int points = *(valid_points.rbegin()) * 2;
                ret += points;
                valid_points.push_back(points);
            } else if (op == "+") {
                if (valid_points.size() < 2) {
                    return -1;
                }
                auto it = valid_points.rbegin();
                int points = *it + *(it+1);
                ret += points;
                valid_points.push_back(points);
            } else {
                int points = std::stoi(op);
                ret += points;
                valid_points.push_back(points);
            }
        }
        return ret;
    }
};

int main() {
    // std::vector<std::string> ops = {"5","2","C","D","+"};
    std::vector<std::string> ops = {"5","-2","4","C","D","9","+","+"};
    std::cout << Solution().calPoints(ops) << std::endl;
    return 0;
}
