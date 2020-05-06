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
    int numSpecialEquivGroups(vector<string>& A) {
        const int len = A.size();
        std::unordered_set<std::string> unique_strs;
        for (auto a: A) {
            convert(a);
            std::sort(a.begin(), a.begin() + (a.size()+1)/2);
            std::sort(a.begin() + (a.size()+1)/2, a.end());
            unique_strs.insert(a);
        }
        return unique_strs.size();
    }

    void convert(string& a) {
        const int len = a.size();
        int left = 0;
        int right = len-1;
        while (left < right) {
            if (left % 2 == 1) ++left;
            if (right % 2 == 0) --right;
            if (left < right) {
                std::swap(a[left++], a[right--]);
            }
        }
    }
};

int main() {
    return 0;
}

