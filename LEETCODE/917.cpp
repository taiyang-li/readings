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
    string reverseOnlyLetters(string& S) {
        const int len = S.size();
        int left = 0;
        int right = len-1;
        while (left < right) {
            while (left < right && ! std::isalpha(S[left]) ) ++left;
            while (left < right && ! std::isalpha(S[right])) --right;
            if (left < right) {
                std::swap(S[left], S[right]);
                ++left;
                --right;
            }
        }
        return S;
    }
};


int main() {
    std::string S = "a-bC-dEf-ghIj";
    std::cout << Solution().reverseOnlyLetters(S) << std::endl;
    return 0;
}

