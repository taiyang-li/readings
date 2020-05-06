#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>


using namespace std;


void min_heapify(int *a, int len, int i);    // 保持堆  i为要更新的结点索引
void build_minheap(int *a, int len);         // 建立最小堆



// 从1000个数里面取出最大的100个数
int main()
{
	const int arr_len = 1000;
	int arr[arr_len];
	
	const int kmax_len = 100;
	int kmax[kmax_len];
	
	// 随机给大数组赋值
	for (int i=0; i<arr_len; i++)
		arr[i] = rand()%10000;

	// 以大数组头kmax_len元素为起点，建立最小堆
	for (int i=0; i<kmax_len; i++)
		kmax[i] = arr[i];
	build_minheap(kmax, kmax_len);
	
	// 找到最大的kmax_len个数
	for (int i=kmax_len; i<arr_len; i++)
	{
		if (arr[i] > kmax[0])  
		{
			kmax[0] = arr[i];
			min_heapify(kmax, kmax_len, 0);
		}
	}

	// 输出最大的kmax_len个数
	for (int i=0; i<kmax_len; i++)
		printf("%d\n", kmax[i]);
	
	
	system("pause");
	return 0;
}




void min_heapify(int *a, int len, int i)  // index表示要更新的结点位置
{
	if (a==NULL && len<=1)
		return;
	

	int min_i = i;
	int left_i = 2*i+1;
	int right_i = 2*i+2;
	
	// 与左孩子比较
	if (left_i < len  && a[left_i] < a[min_i])
		min_i = left_i;

	// 与右孩子比较
	if (right_i < len && a[right_i] < a[min_i])
		min_i = right_i;
	
	// 交换根节点和最大值节点, 进行下一步递归
	if (i != min_i)
	{
		int tmp = a[i];
		a[i] = a[min_i];
		a[min_i] = tmp;
		min_heapify(a, len, min_i);
	}
}





void build_minheap(int *a, int len)
{
	if (a == NULL || len <= 1)
		return;
	
	for (int i = len/2-1; i>=0; i--)
		min_heapify(a, len, i);
}
