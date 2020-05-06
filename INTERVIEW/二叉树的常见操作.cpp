#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <exception>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>
using namespace std;

struct TreeNode
{
	int	val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int val):val(val), left(NULL),right(NULL){} ; 
};
void pre_traversal(TreeNode *node)
{
	if(!node)
		return;
	cout <<"\t"<<node->val;
	pre_traversal(node->left);
	pre_traversal(node->right);
}
void in_traversal(TreeNode *node)
{
	if(!node)
		return;
	in_traversal(node->left);
	cout <<"\t"<<node->val;
	in_traversal(node->right);
}
void post_traversal(TreeNode *node)
{
	if(!node)
		return;
	post_traversal(node->left);
	post_traversal(node->right);
	cout <<"\t"<<node->val;
}


void insert(TreeNode **root, int val)
{
	TreeNode *current = *root;
	TreeNode *parent = NULL;
	while(current)
	{
		if(current -> val == val)
			return;
		parent = current;
		if(current->val > val)
			current = current->left;
		else
			current = current->right;
	}
	TreeNode *p = new TreeNode(val); 
	p->val = val;
	p->left = NULL;
	p->right = NULL;
	if(parent)
		if(parent->val > val)
			parent->left = p;
		else
			parent->right = p;
	else
		*root = p;
}

TreeNode *findNode(TreeNode *root, int val)
{
	TreeNode *node = root;
	while(node)
	{
		if(node->val == val)
			return node;
		else
			node = node->val < val ? node->right : node->left;
	}
	return NULL;
}

void deleteNode(TreeNode **root, int val)
{
	if(!*root)
		return;
	TreeNode *t = findNode(*root, val);
	if(!t)
		return;
	if(!t->left)
	{
		TreeNode *tmp = t;
		t = t->right;
		delete tmp;
	}
	else if(!t->right)
	{
		TreeNode *tmp = t;
		t = t->left;
		delete tmp;
	}

}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout <<"Usage: ./"<< argv[0] <<"node1 node2 node3 ...."<<endl; 
		exit(1);
	}
	time_t lt = time(NULL);
	srand(lt);
	vector<int > vals;
	for(int i=1; i<argc; i++)
		vals.push_back(atoi(argv[i]));
	TreeNode *btree = NULL;
	for(int i=0; i<vals.size() ;i++)
	{
		insert(&btree, vals[i]);	
	}
	pre_traversal(btree);
	cout << endl;
	in_traversal(btree);
	cout << endl;

	int val = vals[rand()%vals.size()];
	cout << "search for "<<val<<endl;
	TreeNode *t = findNode(btree, val);
	if(t)
		cout << t->val << endl;

//	for(int i=0; i<vals.size() ;i++)
	{
		deleteNode(&btree, 12);
//		deleteNode(&btree, vals[i]);
		in_traversal(btree);
		cout << endl;
		pre_traversal(btree);
		cout << endl;
	}
}

