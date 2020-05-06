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
    vector<vector<int>> threeSum(vector<int> &num) {
        vector<vector<int>> result;   // 输出结果
        vector<int> num1 = num;

		if (num1.size() < 3)
		    return result;

	    sort(num1.begin(), num1.end());  //  时间复杂度 O(n*logn)

		int last_t = INT_MIN;
        for(int i=num.size()-1; i>=2; i--)       // 时间复杂度 O(n^2)
        {
            // 检测是否有重复元素，如有，则跳过
            int t = num1.back();   // 末尾一个元素
			num1.pop_back();      // 去掉末尾一个元素 在重复和不重复的情况下
			if (t == last_t)        // 如果有元素重复
			{
				continue;
			}
			last_t = t;

            // 求取符合条件的两个数
            vector<vector<int>> tt = twoSum1(num1, -t);

            if (tt.size())               // 找到了
            {
                for(int j=0; j<tt.size(); j++)
                {
                    vector<int> ttt = tt[j];
                    ttt.push_back(t);
					sort(ttt.begin(), ttt.end());
                    result.push_back(ttt);
                }
            }
        }
		return  result;
    }


    vector<vector<int>> twoSum(vector<int> &numbers, int target) {
        vector<vector<int>> result;
        map<int, int> table;         // 用于记录互补的数字及其位置
		map<int, int> table1;        // 用于记录table中元素的访问个数
        int i;
        int len = numbers.size();

        for(i=0; i<len; i++)
        {

            if (table.find(numbers[i]) !=  table.end())  // 如果能够找到
            {
				table1[numbers[i]]++;
				if (table1[numbers[i]] == 1)
				{
					vector<int> t;
					t.push_back(numbers[table[numbers[i]]]);
					t.push_back(numbers[i]);
					result.push_back(t);
				}
            }
            else
            {
                table[target - numbers[i]] = i;
				table1[target - numbers[i]] = 0;
            }
        }
        return result;
    }



    vector<vector<int>> twoSum1(vector<int> &numbers, int target) {
        vector<vector<int>> result;
        int i=0;
        int j=numbers.size()-1;

        if (numbers.size() < 2)
            return result;

        // 数组长度大于2时
        int pre_left = INT_MIN;
        int pre_right = INT_MAX;

        while(i<j)
        {

            // 根据和进行动态调整
            if (numbers[i] + numbers[j] > target)
                j--;
            else if (numbers[i] + numbers[j] == target)
            {
                if (numbers[i] == pre_left && numbers[j] == pre_right)
                {
                    i++;
                    j--;
                    continue;
                }
                else
                {
                    vector<int> t;
                    t.push_back(numbers[i]);
                    t.push_back(numbers[j]);
                    result.push_back(t);
                    pre_left = numbers[i];
                    pre_right = numbers[j];
                    i++;
                    j--;
                }
            }
            else
                i++;
        }
        return result;
    }
};

int main() {
    return 0;
}

