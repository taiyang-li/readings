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
    string convert(string s, int nRows) {
        if (nRows==0)  return "";
        if (nRows==1)  return s;

        vector<string> ss(nRows, "");
    	string result;

    	int len = s.size();
    	int cur_row = 0;
    	int drct = 1;
    	int t = 0;

    	while(t<len)
    	{
    		ss[cur_row] += s[t];

    		if (cur_row == 0 && drct == -1)
    		{
    			drct = 1;
    		}
    		if(cur_row == nRows-1 && drct == 1)
    		{
    			drct = -1;
    		}
    		cur_row  += drct;

    		t++;
    	}

    	result = "";
    	for(t=0; t<nRows; t++)
    	{
    		result += ss[t];
    	}
    	return result;
        }
};

int main() {
    return 0;
}

