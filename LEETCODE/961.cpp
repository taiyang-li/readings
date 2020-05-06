#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
#include <vector>
using std::vector;


class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int len = A.size();
        for (int i=0; i<len; ++i) {
            if (i+1 < len && A[i] == A[i+1]) {
                return A[i];
            } 
            if (i+2 < len && A[i] == A[i+2]) {
                return A[i+2];
            }
        }
        return A[0];
    }
};

int main() {
    return 0;
}
