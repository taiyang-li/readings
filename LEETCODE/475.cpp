#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <set>
using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        assert(heaters.size() > 0);
        std::set<int> house_set(houses.begin(), houses.end());
        std::set<int> heater_set(heaters.begin(), heaters.end());
        int ret = 0;
        for (auto it=heater_set.begin(); it != heater_set.end(); ++it) {
            auto next_it = it;
            std::advance(next_it, 1);
            if (next_it == heater_set.end()) {
                break;
            }

            auto left = house_set.upper_bound(*it);
            auto right = house_set.lower_bound(*next_it);
            if (left == right) {
                continue;
            }
            /*
            if (std::distance(left, right) == 1) {
                ret = std::max(ret, std::min(*left-*it, *next_it-*left));
                continue;
            }
            */
            int tmp = *next_it - *it;
            tmp = std::min(tmp, *next_it - *left);
            for (auto curr=left; curr!=right; ++curr) {
                int left_radius= *curr - *it;
                int right_radius = 0;
                auto next = curr;
                std::advance(next, 1);
                if (next != right) {
                    right_radius = *next_it - *next;
                    tmp = std::min(tmp, std::max(left_radius, right_radius));
                } else {
                    tmp = std::min(tmp, left_radius);
                }
            }
            ret = std::max(ret, tmp);
        }
        ret = std::max(ret, *heater_set.begin() - *house_set.begin());
        ret = std::max(ret, *house_set.rbegin() - *heater_set.rbegin());
        return ret;
    }
};

int main() {
    /*
    std::vector<int> houses = {282475249,622650073,984943658,144108930,470211272,101027544,457850878,458777923};
    std::vector<int> heaters = {823564440,115438165,784484492,74243042,114807987,137522503,441282327,16531729,823378840,143542612};
    */
    std::ifstream ifs("./mylog");
    std::string house_line;
    std::getline(ifs, house_line);
    std::string heater_line;
    std::getline(ifs, heater_line);
    
    std::istringstream iss1(house_line);
    std::vector<int> houses;
    while (iss1.good()) {
        int tmp = 0;
        iss1 >> tmp;
        houses.push_back(tmp);
    }
    std::istringstream iss2(heater_line);
    std::vector<int> heaters;
    while (iss2.good()) {
        int tmp = 0;
        iss2 >> tmp;
        heaters.push_back(tmp);
    }
    std::cout << Solution().findRadius(houses, heaters) << std::endl;
    return 0;
}
