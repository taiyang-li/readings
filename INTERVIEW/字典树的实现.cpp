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

const int CHAR_NO = 26;
typedef unsigned int uint;

// 字典数结点定义
struct Node 
{
	uint label1;
	uint label2;
	Node *next[CHAR_NO];
	Node(int l1, int l2): label1(l1), label2(l2)
	{
		for (int i=0; i<CHAR_NO; i++)
			next[i] = NULL;
	}
};


// 创建字典树
Node *build_tree();
// 插入结点
void insert_node(Node *root, string str, uint l1, uint l2);
// 删除结点
void delete_node(Node *root, string str);
// 更改某个结点的值

// 读入某一个结点的值

// 得到下一个有效结点对应的字符串
pair<string, Node *> next_valid_node(string, Node *);

int main()
{
	
	system("pause");
}


Node *build_tree()
{
	Node *r = new Node(0,0);
	return r;
}

void insert_node(Node *root, string str, uint l1, uint l2)
{
	if (str.empty() || root == NULL)
		return;
	
	// 遍历每一个结点
	int len = str.size();
	Node *cur = root;
	for (int i=0; i<len; i++)
	{
		char c = str[i];
		if (cur->next[c-'a'] == NULL)
			cur->next[c-'a'] = new Node(0,0); 
		cur = cur->next[c-'a'];
	}
	cur->label1 = l1;
	cur->label2 = l2;
}



void delete_node(Node *root, string str)
{
	if (str.empty() || root == NULL)
		return;

	int idx = -1;

	pair<Node *, int> pre_pt(root, -1);
	pair<Node *, int> pt;
	
	while(1)
	{
		pt = next_valid_node(str, pre_pt);

		// 判断异常情况(不存在相应结点或相应结点为无效)
		if (pre_pt.first == NULL || pre_pt.second == -1)
			return;
		
		// 如果是叶子结点, 则退出
		int i;
		for (i=0; i<CHAR_NO; i++)
		{
			if (pt.first->next[i] != NULL)
				break;
		}
		if (i==CHAR_NO)  // 是叶子结点
			break;

		pre_pt = pt;
	}
	
	int start = pre_pt.second+1;
	int end = pt.second;
	Node *p = pre_pt.first;
	Node *s = NULL;
	for (int i=start; i<=end; i++)
	{
		p = p->next[str[i]-'a'];
		
	}
	
	
}


pair<Node *, int> next_valid_node(string str, pair<Node *, int> pt)
{	
	
	pair<Node *, int>  res(pt);

	Node *node = pt.first;
	int idx = pt.second;

	int len = str.size();
	if (len == +1)
		return res;

	while(idx<len-1)
	{
		char c = str[++idx];
		node = node->next[c-'a'];
		if (node == NULL)    // 异常情况1  索引字符串不能用树的路径表示
		{
			res.first = NULL;
			res.second = -1; 
			return res;
		}
		if (node->label1 != 0 && node->label2 != 0)
			break;
	}
	// 异常情况2： 索引字符串对应的结点并非有效结点
	if (node->label1 == 0 || node->label2 == 0)
	{
		res.first = NULL;
		res.second = -1;
		return res;
	}
	
	res.first = node;
	res.second = idx;
	return res;
}




