#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

class CmpByHeight {
public:
    bool operator()(const pair<int, int>& left, const pair<int, int>& right) {
        if (left.first < right.first) {
            return true;
        } else if (left.first == right.first) {
            return std::greater<int>()(left.second, right.second);
        } else {
            return false;
        }
    }
};

class Solution {
public:
    vector<pair<int, int> > reconstructQueue(vector<pair<int, int>>& people) {
        if (people.size() <= 1) {
            return people;
        }
    
        vector<pair<int, int> > ret(people.size());
        std::sort(people.begin(), people.end(), CmpByHeight());
        std::map<int, int> index2unassigned;
        std::map<int, int> unassigned2index;
        for (size_t i=0; i<people.size(); ++i) {
            index2unassigned[i] = i;
            unassigned2index[i] = i;
        }

        int assign_index = 0;
        for (size_t i=0; i<people.size(); ++i) {
            const auto& item = people[i];
            assign_index = unassigned2index[item.second];
            ret[assign_index] = item;
            update_status(assign_index, index2unassigned, unassigned2index);
        }
        return ret;
    }

    void update_status(int index, 
            std::map<int, int>& index2unassigned, 
            std::map<int, int>& unassigned2index) {
        int unassigned = index2unassigned[index];
        auto mit = index2unassigned.find(index);
        ++mit;
        index2unassigned.erase(index);
        unassigned2index.erase(unassigned);
        for (; mit != index2unassigned.end(); ++mit) {
            unassigned = mit->second;
            unassigned2index.erase(unassigned);
            
            mit->second--;
            unassigned2index[mit->second] = mit->first;
        }
    }
};


int main() {
    vector<pair<int, int> > input = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};
    vector<pair<int, int> > output = Solution().reconstructQueue(input);
    for (auto x : output) {
        std::cout << x.first << ", " << x.second << std::endl;
    }
    return 0;
}
