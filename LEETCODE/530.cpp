#include <iostream>
#include <stack>
#include <climits>
#include <algorithm>
#include "tree.h"
using std::stack;
using std::min;


int getMinimumDifference(TreeNode* root)
{
  TreeNode* curr = root;
  TreeNode* prev = NULL;
  stack<TreeNode*> s;
  int ret = INT_MAX;

  while(curr || !s.empty())
  {
    while (curr)
    {
      s.push(curr);
      curr = curr->left;
    }
    curr = s.top();
    s.pop();

    if (prev)
      ret = min(ret, curr->val - prev->val);
    prev = curr;
    curr = curr->right;
  }
  return ret;
}

int main()
{
  vector<int> nums = {1, null, 5, null, null, 3, null};
  TreeNode* root = ::generateTree(nums);
  ::showTree(root);
  std::cout << getMinimumDifference(root) << std::endl;
}
