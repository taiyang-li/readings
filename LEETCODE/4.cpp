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
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if((m+n)%2 == 0)
        	return (findKth(A, m, B, n, (m+n)/2) + findKth(A, m, B, n, (m+n)/2 + 1))/2.0;
        else
        	return findKth(A, m, B, n, (m+n+1)/2);
    }


    int findKth(int a[], int m, int b[], int n, int k)    // 找到a和b中的第k个元素
    {
        // 左数组长度小于右数组
    	if (m>n)
    		return findKth(b, n, a, m, k);

        // a为空
    	if(m==0)
    		return b[k-1];

    	// b为空
    	if(n==0)
    		return a[k-1];

    	if(k==1)
    		return min(a[0], b[0]);

    	int pa = min(k/2, m);     // a取前pa个数
    	int pb = k-pa;            // b取前pb个数

    	// a的最后一个结点大于b
    	if (a[pa-1] == b[pb-1])
    		return a[pa-1];

    	if(a[pa-1] > b[pb-1])
    		return findKth(a, m, b+pb, n-pb, k-pb);

    	return findKth(a+pa, m-pa, b, n, k-pa);
    }
};

int main() {
    return 0;
}

