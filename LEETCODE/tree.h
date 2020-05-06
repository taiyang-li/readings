#ifndef __LEETCODE_TREE_H__
#define __LEETCODE_TREE_H__

#include <vector>
#include <cassert>
#include <string>
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using std::vector;
using std::queue;
using std::string;
using std::max;
using std::min;

#define null -1

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

static void insertTree(TreeNode* root, int val)
{
  assert(root != NULL);
  TreeNode* tmp = root;
  TreeNode* parent = NULL;
  while (tmp)
  {
    parent = tmp;
    if (val < tmp->val)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }
  if (val < parent->val)
    parent->left = new TreeNode(val);
  else
    parent->right = new TreeNode(val);
}

static TreeNode* createTree(vector<int>& nums)
{
  if (nums.empty())
    return NULL;

  TreeNode* root = new TreeNode(nums[0]);
  for (auto it=nums.begin()+1; it!=nums.end(); ++it)
    insertTree(root, *it);
  return root;
}

static TreeNode* generateTree(vector<int>& nums)
{
  if (nums.empty() || nums[0] == null)
    return NULL;

  vector<TreeNode*> nodes;
  for (size_t i=0; i<nums.size(); ++i)
  {
    TreeNode* node = NULL;
    if (nums[i] != null)
    {
      node = new TreeNode(nums[i]);
    }
    nodes.push_back(node);

    if (i != 0 && nodes[(i-1)/2])
    {
      if (i % 2 == 1)
        nodes[(i-1)/2]->left = node;
      else 
        nodes[(i-1)/2]->right = node;
    }
  }
  return nodes[0];
}

static TreeNode* generateTree(vector<int>& nums, int idx)
{
  if (nums.empty() || idx >= (int)nums.size() || nums[idx] == null)
    return NULL;

  TreeNode* node = new TreeNode(nums[idx]);
  std::cout << "idx:" << idx << ",val:" << node->val << std::endl;
  node->left = generateTree(nums, idx*2+1);
  node->right = generateTree(nums, idx*2+2);
  return node;
}
static void deleteTree(TreeNode* root)
{
  assert(root != NULL);
  TreeNode* lchild = root->left;
  TreeNode* rchild = root->right;
  delete root;
  if (lchild)
    deleteTree(lchild);
  if (rchild)
    deleteTree(rchild);
}

static TreeNode* searchTree(TreeNode* root, int val)
{
  assert(root != NULL);
  
  TreeNode* tmp = root;
  while (tmp)
  {
    if (tmp->val == val)
      return tmp;

    if (val < tmp->val)
      tmp = tmp->left;
    else 
      tmp = tmp->right;
  }
  return NULL;
}

static bool treePath(TreeNode* root, TreeNode* target, vector<TreeNode*>& nodes)
{
  nodes.clear();
  TreeNode* tmp = root;
  while (tmp)
  {
    nodes.push_back(tmp);

    if (tmp == target)
      return true;

    if (target->val < tmp->val)
      tmp = tmp->left;
    else 
      tmp = tmp->right;
  }
  return false;
}

enum Direction {LEFT, RIGHT};
static TreeNode* farNode(TreeNode* root, Direction d) 
{
  if (! root)
    return NULL;

  TreeNode* tmp = root;
  if (d == RIGHT)
  {
    while (tmp->right)
      tmp = tmp->right;
  }
  else
  {
    while (tmp->left)
      tmp = tmp->left;
  }
  return tmp;
}

static int treeDepth(TreeNode* root)
{
  if (! root)
    return 0;

  int ldepth = treeDepth(root->left);
  int rdepth = treeDepth(root->right);
  return 1 + (ldepth > rdepth ? ldepth : rdepth);
}

struct ShowTreeInfo
{
  int y;
  int x;
  TreeNode* node;
};

#define FIELDSIZE 2
static void showTree(TreeNode* root)
{
  assert(root != NULL);

  // generate table
  int depth = treeDepth(root);
  string line;
  int width = (1<<depth) - 1;
  for (int i=0; i<width; i++)
    line.append(string(FIELDSIZE, ' '));
  vector<string> table(depth*2-1, line);

  char d_format[8];
  char s_format[8];
  sprintf(d_format, "%%-%dd", FIELDSIZE);
  sprintf(s_format, "%%-%ds", FIELDSIZE);

  queue<ShowTreeInfo> node_queue;
  ShowTreeInfo sinfo, tmp;
  sinfo.y = 1;
  sinfo.x = (width+1)/2;
  sinfo.node = root;
  node_queue.push(sinfo);
  while (! node_queue.empty())
  {
    tmp = node_queue.front();
    node_queue.pop();

    char buf[8];
    sprintf(buf, d_format, tmp.node->val);
    table[tmp.y-1].replace(FIELDSIZE*(tmp.x-1), FIELDSIZE, buf);

    if (tmp.node->left)
    {
      ShowTreeInfo linfo;
      linfo.y= tmp.y + 2;
      linfo.x = tmp.x - (1 << (depth - (linfo.y+1)/2));
      linfo.node = tmp.node->left;
      node_queue.push(linfo);

      sprintf(buf, s_format, "/");
      table[tmp.y].replace(FIELDSIZE*(tmp.x-2), FIELDSIZE, buf);
    }

    if (tmp.node->right)
    {
      ShowTreeInfo rinfo;
      rinfo.y = tmp.y + 2;
      rinfo.x = tmp.x + (1 << (depth - (rinfo.y+1)/2));
      rinfo.node = tmp.node->right;
      node_queue.push(rinfo);

      sprintf(buf, s_format, "\\");
      table[tmp.y].replace(FIELDSIZE*tmp.x, FIELDSIZE, buf);
    }
  }

  for (auto it=table.begin(); it!=table.end(); ++it)
    std::cout << *it << std::endl;
}


static void breadthFirstTraversal(TreeNode* root, vector<int>& nums)
{
  nums.clear();
  if (! root)
    return;

  queue<TreeNode*> nodes;
  nodes.push(root);
  while (! nodes.empty())
  {
    TreeNode* tmp = nodes.front();
    nodes.pop();
    nums.push_back(tmp->val);

    if (tmp->left)
      nodes.push(tmp->left);
    if (tmp->right)
      nodes.push(tmp->right);
  }
}

static void preorderTraversal(TreeNode* root, vector<int>& nums)
{
  if (! root)
    return;

  nums.push_back(root->val);
  if (root->left)
    preorderTraversal(root->left, nums);
  if (root->right)
    preorderTraversal(root->right, nums);
}

static void inorderTraversal(TreeNode* root, vector<int>& nums)
{
  if (! root)
    return;

  nums.clear();
  if (root->left)
  {
    vector<int> tmp;
    inorderTraversal(root->left, tmp);
    nums.insert(nums.end(), tmp.begin(), tmp.end());
  }
  nums.push_back(root->val);
  if (root->right)
  {
    vector<int> tmp;
    inorderTraversal(root->right, tmp);
    nums.insert(nums.end(), tmp.begin(), tmp.end());
  }
}

static void postorderTraversal(TreeNode* root, vector<int>& nums)
{
  if (! root)
    return;

  nums.clear();
  if (root->left)
  {
    vector<int> tmp;
    inorderTraversal(root->left, tmp);
    nums.insert(nums.end(), tmp.begin(), tmp.end());
  }
  if (root->right)
  {
    vector<int> tmp;
    inorderTraversal(root->right, tmp);
    nums.insert(nums.end(), tmp.begin(), tmp.end());
  }
  nums.push_back(root->val);
}
#endif
