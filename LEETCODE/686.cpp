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
    int repeatedStringMatch(const string& A, const string& B) {
        const int lena = A.size();
        for (int i=0; i<lena; ++i) {
            if (A[i] != B[0]) {
                continue;
            }
            auto ret = helper(A, B, i);
            if (ret != -1) {
                return ret;
            }
        }
        return -1;
    }

    int helper(const string& A, const string& B, int pos) {
        int idxa = pos;
        int idxb = 0;
        const int lena = A.size();
        const int lenb = B.size();
        while (idxb < lenb && A[idxa] == B[idxb]) {
            idxa = (idxa + 1) % lena;
            ++idxb;
        }
        if (idxb < lenb) {
            return -1;
        }
        return 1 + (lenb - (lena - pos) + lena - 1) / lena;
    }
};

int main() {
    return 0;
}

