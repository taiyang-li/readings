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
    int trap(int A[], int n) {

        // 小trick: 在A的周围补零, 这样可以避免很多边界条件的判定
        vector<int> aa;
        aa.push_back(0);            // 在头部插入0
        for (int i=0; i<n; i++)     // 复制数组
        {
            aa.push_back(A[i]);
        }
        aa.push_back(0);        // aa共有n+2个元素


		/*cout << "aa: ";
		printv(aa);*/

        // 对数组aa进行微分操作
        vector<int> d;
        for(int i=0; i<=n; i++)          // 共有n+1个差分值
        {
            d.push_back(aa[i+1] - aa[i]);        // d[i] = aa[i+1] - aa[i];
        }

		/*cout << "d: ";
		printv(d);*/

        // 扫描获得极大值， d[i-1] > 0 && d[i+1] < 0
        vector<int> max_tb;
        int len = d.size();          // n+1
        int i = 1;
		while(i<len)
        {
            if (d[i-1] > 0  && d[i] < 0)    ///  极值点的特性
            {
                max_tb.push_back(i);
				i += 2;
            }
			else if (d[i-1] == 0 && d[i] < 0)
			{
				int t = i;
				while(d[t-1] == 0 && t-1>=0) t--;
				if (t-1<0 || d[t-1]>0)   //  符合极大值的条件
				{
					// printi(1000);
					max_tb.push_back(i);
				}
				i += 2;
			}
			else if (d[i-1] > 0  && d[i] == 0)
			{
				int t = i;
				while(d[t] == 0 && t<len)  t++;
				if (t==len)           // 已经到达了右边界
				{
					//printi(1000);
					max_tb.push_back(i);
					break;
				}
				else if (d[t] < 0)
				{
					//printi(1000);
					max_tb.push_back(i);
					i = t+1;
				}
				else
				{
				    i = t+1;
				}
			}
			else
			{
				i++;
			}
        }
		/*cout << "max_tb: ";
		printv(max_tb);*/

        // 从极大值得到水滴体积
        len = max_tb.size();
        if (len < 2)    // 如果极值点的数目小于2，则形不成容器, trap的水滴面积则为0
			return 0;

        int sum = get_area(aa, max_tb, 0, len-1);
        return sum;

    }


    // left表示左边的极大值在max_tb中的位置 right表示右边的极大值点在max_tb中的位置
    int get_area(vector<int> &aa, vector<int> &max_tb, int left, int right)
    {
		//cout << "left: " << left << " right: " << right << endl;

		// P1
        if(left == right)
		{
			//cout << 0 << endl;
			return 0;
		}

        // P2
        //当left right 相邻时，可以直接计算水滴面积
        if (left + 1 == right)       //如果二者的间距为1
        {
            int sum=0;
            int h = min(aa[max_tb[left]], aa[max_tb[right]]);        // 找到两端最小者
			int st = max_tb[left]+1;
			int ed = max_tb[right]-1;
            for(int i=st; i<=ed; i++)
            {
                if (h>aa[i])          // 只有低于水平线才会累加
                    sum += h-aa[i];
            }
			//cout << sum << endl;
            return sum;
        }

		// P3: left right 的距离大于1时，根据动态规划的原则计算面积
        // 首先找到最大值位置
        int max_idx = -1;
        int max_value = INT_MIN;
		int st = left;
		int ed = right;
        for(int i=st; i<=ed; i++)
        {
            if(aa[max_tb[i]] > max_value)
            {
                max_idx = i;
                max_value = aa[max_tb[i]];
            }
        }

        // 其次找到次最大值位置
        int next_idx = -1;
        int next_value = INT_MIN;
		st = left;
		ed = right;
        for (int i=st; i<=ed; i++)
        {
            if (i != max_idx)
            {
                if (aa[max_tb[i]] > next_value)
                {
                    next_value = aa[max_tb[i]];
                    next_idx = i;
                }
            }
        }


        // 现在已经找到了最大值的位置以及次最大值的位置， 计算最大值和次最大值之间的面积
        int sum = 0;
        st = min(max_idx, next_idx);        // 最大面积的起点
        ed = max(max_idx, next_idx);        // 最大面积的终点
		int st1 = max_tb[st] + 1;
		int ed1 = max_tb[ed] - 1;
		int h = min(max_value, next_value);

        for (int i=st1; i<=ed1; i++)
        {
			if (h>aa[i])
			{
				sum += h-aa[i];
			}
        }

        sum += get_area(aa, max_tb, left,   st);           // 总面积加上左边部分面积
        sum += get_area(aa, max_tb,  ed, right);           // 总面积加上右边部分面积
		//cout << sum << endl;
        return sum;
    }
};

int main() {
    return 0;
}

