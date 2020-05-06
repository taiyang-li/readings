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
    bool validMountainArray(vector<int>& A) {
        const int len = A.size();
        if (len < 3) {
            return false;
        }

        int i = 0;
        for (; i+1 < len && A[i] < A[i+1]; ++i);
        if (i == 0 || i+1 == len) {
            return false;
        }
        
        for (; i+1 < len && A[i] > A[i+1]; ++i);
        return i+1 == len;
    }
};
int main() {
    return 0;
}

