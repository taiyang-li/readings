#include <map>
#include <unordered_map>
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
    bool hasGroupsSizeX(vector<int>& deck) {
        std::unordered_map<int, int> counts;
        for (auto x : deck) {
            counts[x]++;
        }
        
        int m = deck.size();
        for (const auto& pair: counts) {
            m = gcd(m, pair.second);
            if (m < 2) {
                return false;
            }
        }
        return true;
    }
    
    int gcd(int m, int n) {
        return n == 0 ? m : gcd(n, m%n);
    }
};

int main() {
    return 0;
}

