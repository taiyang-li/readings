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
    int bitwiseComplement(int N) {
        if (N == 0) return 1;
        int weight = 1;
        int n = N;
        while (n > 0) {
            n >>= 1;
            weight <<= 1;
        }
        return (weight - 1) ^ N;
    }
};

int main() {
    return 0;
}

