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
    static const int SIZE = 8;
    string largestTimeFromDigits(vector<int>& A) {
        std::sort(A.begin(), A.end());
        char ret[SIZE];
        ret[0] = 0;
        do {
            if ((A[0] <= 1 || (A[0] == 2 && A[1] <= 3)) && A[2] <= 5) {
                char buf[SIZE];
                ::snprintf(buf, SIZE, "%d%d:%d%d", A[0], A[1], A[2], A[3]);
                if (::strncmp(buf, ret, SIZE) > 0) {
                    ::strncpy(ret, buf, SIZE);
                }
            }
        } while (std::next_permutation(A.begin(), A.end()));
        return std::string(ret);
    }
}; 


int main() {
    return 0;
}

