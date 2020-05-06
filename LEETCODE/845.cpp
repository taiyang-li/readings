#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
        const int len = A.size();
        int ret = 0;
        int start = 0;
        bool in_incr = false;
        bool in_decr = false;
        for (int i=0; i<len;) {
            start = i;
            in_incr = false;
            in_decr = false;
            while (i < len-1 && A[i] < A[i+1]) {
                in_incr = true;
                i++;
            }
            if (! in_incr) {
                i++;
                continue;
            }
            
            in_decr = false;
            while (i < len-1 && A[i] > A[i+1]) {
                in_decr = true;
                i++;
            }
            if (! in_decr) {
                i++;
                continue;
            }
            ret = std::max(ret, i-start+1);
        }
        return ret;
    }
};

int main() {
    std::vector<int> A = {875,884,239,731,723,685};
    std::cout << Solution().longestMountain(A) << std::endl;
    return 0;
}
