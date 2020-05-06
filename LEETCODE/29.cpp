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
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == 0 || divisor == 0)
            return 0;
        if (dividend < 0)
            if (dividend != 0x80000000)
				return -divide(-dividend, divisor);
			else
				return divisor>0 ? (-1-divide(-(dividend+divisor), divisor))
								: (1-divide(-(dividend-divisor), divisor));
        if (divisor < 0)
            if (divisor != 0x80000000)
                return -divide(dividend, -divisor);
            else
                return dividend == 0x80000000 ? 1 : 0;

        if (dividend < divisor)
            return 0;

        //  除数和被除数都是正整数的情况
        // vector<int> table;
        long long  t = divisor;
        int count = 0;
        while(t<=dividend)
        {
            count++;
            t = t<<1;
        }

        int cur_idx = count-1;   // 当前符合条件的除数位置
        int result = 0;
        while(cur_idx>=0 && dividend > 0)
        {
            result += 1<<cur_idx;
            dividend -= divisor<<cur_idx;
            while(cur_idx>=0 && dividend < divisor<<cur_idx)
                cur_idx--;
        }
        return  result;
    }
};

int main() {
    return 0;
}

