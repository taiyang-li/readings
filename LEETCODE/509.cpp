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
    int fib(int N) {
        int a = 0;
        int b = 1;
        if (N == 0) return a;
        if (N == 1) return b;
        for (int i=0; i<N-1; ++i) {
            b = a+b;
            a = b-a;
        }
        return b;
    }
};

int main() {
    return 0;
}

