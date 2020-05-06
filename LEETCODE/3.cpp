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
    int lengthOfLongestSubstring(string s) {
    	int len = s.size();
    	if (len == 0)  return 0;
    	int i;
    	int j;
    	int max_len = 1;
    	char isused[256] = {0,0,0};
    	int t;
    
    	for(i=0; i<len; i++)
    	{
    		// 首先对isused数组进行清零
    		for(j=0; j<256; j++)
    		{
    			isused[j] = 0; 
    		}
    		
    		t = i;
    		while(isused[s[t]] == 0 &&  t<len)
    		{
    			isused[s[t]] = 1;
    			t++;
    		}
    		if (t-i > max_len)
    		{
    			max_len = t-i;
    		}
    	}
    	return max_len;
    }
};

int main() {
    return 0;
}

