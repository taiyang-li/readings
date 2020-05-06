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
    int mirrorReflection(int p, int q) {
        int tmp1 = gcd(p, q);
        int tmp2 = q/tmp1;
        // k为竖直方向走的倍数
        // tmp3为水平方向走的倍数
        for (int k=tmp2; ; k += tmp2) {
            int tmp3 = k*p/q;
            if (k % 2 == 0) {
                if (tmp3 % 2 != 0) {
                    return 0;
                }
            } else {
                return (tmp3 % 2 == 0) ? 2 : 1;
            }
        }
    }

    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }
};

int main() {
    int p = 2;
    int q = 1;
    std::cout << Solution().mirrorReflection(p, q);
    return 0;
}
