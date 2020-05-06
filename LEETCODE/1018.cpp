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
using std::vector;
using std::string;

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        int curr = 0;
        const int len = A.size();
        std::vector<bool> ret(len, false);
        for (int i=0; i<len; ++i) {
            curr = ((curr << 1) | A[i]) % 5; 
            ret[i] = curr == 0;
        }
        return ret;
    }
};

int main() {
    return 0;
}

