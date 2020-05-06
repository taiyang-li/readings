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
    int reverse(int x) {
	bool neg = (x>=0) ? false : true;
	long long xx=0;
	int t ;
	x = x * (neg == true? -1 : 1);
	while(x)
	{
		t = x%10;
		xx = 10*xx + t;
		x = x/10;
	}
	if (xx > 0x7fffffff)
	{
		return 0;
	}

	xx = xx * (neg == true? -1 : 1);
	return (int)xx;
    }
};
int main() {
    return 0;
}

