#include <algorithm>
#include <vector>
#include "tree.h"
using std::swap;
using std::vector;

TreeNode* invertTree(TreeNode* root)
{
  if (! root)
    return NULL;

  root->left = invertTree(root->left);
  root->right =  invertTree(root->right);
  swap(root->left, root->right);
  return root;
}

int main()
{
  vector<int> nums = {4, 2, 7, 1, 3, 6, 9};
  TreeNode* root = generateTree(nums);
  showTree(root);
  
  root = invertTree(root);
  showTree(root);
  return 0;
}
