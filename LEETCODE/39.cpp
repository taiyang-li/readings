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
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> t;
        vector<vector<int>> res;
        t = combinationSum_core(candidates, target);

        if (t[0][0] != -1)
        {
            res = t;
        }
        return res;

    }

    vector<vector<int>> combinationSum_core(vector<int> &candidates, int target) {
        vector<vector<int>>  res;

		// 意外情况
		if (candidates.empty())
		{
			vector<int> t(1,-1);
			res.push_back(t);
			return res;
		}


        if (candidates.size() == 1)         // 当只有一个元素时
        {
			if (target % candidates[0] == 0)     // target能被candidates[0]整除
			{
				const int n = target/candidates[0];
				vector<int> t(n, candidates[0]);
				res.push_back(t);
				return res;
			}
			else
            {
                vector<int> t(1,-1);
                res.push_back(t);
                return res;
            }
        }

        sort(candidates.begin(), candidates.end());

		if (candidates[0] > target)
		{
			vector<int> t(1,-1);
			res.push_back(t);
			return res;
		}
		// 加入含有跟第一个元素的情况
		else if (candidates[0] == target)
		{
			vector<int> t(1,candidates[0]);
			res.push_back(t);
			return res;
		}


        vector<int>   candidates_bk = candidates;      // 备份candidates_bk
        vector<vector<int>> t = combinationSum_core(candidates, target-candidates[0]);
        if (t[0][0] != -1)
        {
			int len1 = t.size();
            for (int i=0; i<len1; i++)
            {
                vector<int> tt;
                tt.push_back(candidates_bk[0]);
				int len2 = t[i].size();
                for (int j=0; j<len2; j++)
                {
                    tt.push_back(t[i][j]);
                }
                res.push_back(tt);
            }
        }

		vector<int> candidates_bk1;
		for (int i=1; i<candidates_bk.size(); i++)
			candidates_bk1.push_back(candidates_bk[i]);
		vector<int>  candidates1 = candidates_bk1;
        // 加入不含有第一个元素的情况
        t = combinationSum_core(candidates1, target);
        if (t[0][0] != -1)
        {
			int len = t.size();
            for (int i=0; i<len; i++)
            {
                res.push_back(t[i]);
            }
        }

		if (res.empty())
		{
			vector<int> t(1,-1);
			res.push_back(t);
		}

		return res;
    }
};

int main() {
    return 0;
}

