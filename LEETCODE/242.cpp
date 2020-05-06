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
    bool isAnagram(const string& s, const string& t) {
        int count1[128] = {0};
        int count2[128] = {0};
        helper(s, count1);
        helper(t, count2);
        return ::memcmp(count1, count2, 128*sizeof(int)) == 0;
    }

    void helper(const string& str, int* count) {
        for (auto ch: str) {
            count[int(ch)]++;
        }
    }
};

int main() {
    return 0;
}

