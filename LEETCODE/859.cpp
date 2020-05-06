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
    bool buddyStrings(const string& A, const string& B) {
        const int lena = A.size();
        const int lenb = B.size();
        if (lena != lenb) {
            return false;
        }
        
        int find_diff = 0;
        char a = -1;
        char b = -1;
        for (int i=0; i<lena; ++i) {
            if (A[i] == B[i]) {
                continue;
            }
            
            ++find_diff;
            if (find_diff == 1)  {
                a = A[i];
                b = B[i];
            } else if (find_diff == 2) {
                if (A[i] != b || B[i] != a) {
                    return false;
                }
            } else {
                return false;
            }
        }
        if (find_diff == 1) {
            return false;
        } 
        if (find_diff == 2) {
            return true;
        }
        std::unordered_set<char> uniq(A.begin(), A.end());
        return lena != uniq.size();
    }
};

int main() {
    std::cout << Solution().buddyStrings("ab", "ab") ;
    return 0;
}

