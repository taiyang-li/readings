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


struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int v) : val(v), next(NULL) {}
};

// 用链表实现一个栈  链表头结点表示栈顶
class my_stack
{
public:
	my_stack()
	{
		head = NULL;
		len = 0;
	}
	
	~my_stack() 
	{
		// 释放申请的内存
		ListNode *p;
		while(head != NULL)
		{
			p = head;
			head = head->next;
			delete p;
		}
	}

	void push(const int &a)
	{
		// 创建新节点
		ListNode *p = new ListNode(a);
		p->next = head;
		head = p;
		len++;
	}
	
	void pop()
	{
		if (head == NULL)
			return;
		
		// 删除头结点
		ListNode *p = head;
		head = head->next;
		delete p;
		len--;
	}

	int top()
	{
		if (head == NULL)
			return INT_MIN; 

		return head->val;
	}


	bool empty()
	{
		return (head == NULL);
	}
	
	int size()
	{
		return len;
	}
	

private:
	int len;   // 当前栈的长度
	ListNode *head;
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
