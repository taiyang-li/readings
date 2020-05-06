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
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int suma = std::accumulate(A.begin(), A.end(), 0);
        int sumb = std::accumulate(B.begin(), B.end(), 0);
        int delta = (suma - sumb)/2;
        std::unordered_set<int> s;
        for (auto a: A) {
            s.insert(a - delta);
        }
        for (auto b: B) {
            if (s.count(b) > 0) {
                return {b+delta, b};
            }
        }
        // impossible get here
        return {};
    }
};

int main() {
    return 0;
}

