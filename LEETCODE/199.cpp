#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <stack>
#include "tree.h"
#include "util.h"
using std::vector;
using std::stack;

struct NodeInfo
{
  TreeNode* node;
  int depth;
  NodeInfo(TreeNode* n, int d) : node(n), depth(d) {}
};

vector<int> rightSideView(TreeNode* root)
{
  vector<int> ret;
  if (! root)
    return ret;

  int depth = treeDepth(root);
  int curr_depth = 0;
  stack<NodeInfo> s;
  NodeInfo ninfo(root, 1);
  s.push(ninfo);
  while (! s.empty() && curr_depth < depth)
  {
    ninfo = s.top();
    s.pop();
    if (ninfo.depth > curr_depth)
    {
      curr_depth = ninfo.depth;
      ret.push_back(ninfo.node->val);
    }

    if (ninfo.node->left)
      s.push(NodeInfo(ninfo.node->left, ninfo.depth+1));
    if (ninfo.node->right)
      s.push(NodeInfo(ninfo.node->right, ninfo.depth+1));
  }
  return ret;
}

int main()
{
  vector<int> nums = {1, 2, 3, 4, 5, null, null, 6, 7, null, null};
  TreeNode* root = generateTree(nums);
  showTree(root);
  
  vector<int> ret = rightSideView(root);
  std::cout << ::stringify(ret) << std::endl;
  return 0;
}

