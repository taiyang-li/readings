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
    string longestPalindrome(string s) {
        // 首先进行预处理
        string ss  = preprocess(s);
        
    	int len = ss.size();
    	int i;
    	int C = 0;
    	int R = 0;
    	int i_mirror;
    	int *P = new int[len];
    
    	// 得到数组P
    	for(i=1; i<len-1; i++)
    	{
    		 i_mirror = 2*C-i;
    		 
    		 if (i>=R)
    		 {
    			 P[i] = 0;
    		 }
    		 else
    		 {
    			 P[i] = min(P[i_mirror], R-i);
    		 }
    			
    		 while(ss[i+P[i]+1] == ss[i-P[i]-1] && (i+P[i]+1)<=(len-1) && (i-P[i]-1)>=1 )
    		 {
    			 P[i]++;
    		 }
    		 
    		 if (i+P[i] > R)
    		 {
    			 R = i+P[i];
    			 C = i;
    		 }
    	}
    	
    	// 找到数组P中最大的
    	int max_len = 0;
    	int center_idx = 0;
    	for(i=1; i<len-1; i++)
    	{
    		if(max_len < P[i])
    		{
    			max_len = P[i];
    			center_idx = i;
    		}
    	}
    
    	delete[] P;
    
    	return s.substr((center_idx-1-max_len)/2, max_len);
    }
    
    
    string preprocess(string s)
    {
    	string  ss = "";
    	int len = s.size();
    	int i;
    
    	if (len == 0)
    	{
    		return "^$";
    	}
    	
    	ss = "^";
    	for(i=0; i<len; i++)
    	{
    		ss = ss + "#" + s[i];
    	}
    	ss = ss + "#$";
    	
    	return ss;
    	
    }
    	
};

int main() {
    return 0;
}

