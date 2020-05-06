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
#include <set>

using namespace std;


// 用数组实现一个栈
class my_stack
{
public:
	my_stack()
	{
		arr = NULL;
		len = 0;
		max_size = 0;
	}
	
	~my_stack() 
	{
		// 释放申请的内存
		delete arr;  
	}

	void push(const int &a)
	{
		// 当前内存空间不够
		if (len == max_size)
		{
			// 重新分配更多内存
			max_size = (len == 0) ? 1 : len*2;
			
			arr = (int *) realloc(arr, max_size * sizeof(int));
			arr[len] = a;
			len++;
		}
		else
		{
			arr[len] = a; 
			len++;
		}
	}
	
	void pop()
	{
        if (len == 0)
            return;
	    len--;  

	}

	int top()
	{
		if (len == 0)
			return INT_MIN;    // 表示错误值
		else
			return arr[len-1];
	}


	bool empty()
	{
		return (len == 0);
	}
	
	int size()
	{
		return len;
	}
	

private:
	int *arr;          // 内存区头指针
	int len;           // 当前栈的长度
	int max_size;      // 内存区的容量
	
};







int main ()
{
	my_stack s;

	if (s.empty())
	{
		cout << "stack empty" << endl;
	}
	
	s.push(1);
	cout << "stack size: " << s.size() << endl;

	int a = s.top();
	cout << "stack top: " << a << endl;
	
	s.pop();

	if (s.empty())
	{
		cout << "stack empty" << endl;
	}

	 getchar();
     return 0;
}
