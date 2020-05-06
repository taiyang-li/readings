#include <algorithm>
#include <vector>
#include "tree.h"
#include "util.h"
using std::max;
using std::vector;

struct TreeInfo
{
  int height;
  int diameter;

  TreeInfo(int h=0, int d=0) : height(d), diameter(d) {}
};

TreeInfo doDiameterOfBinaryTree(TreeNode* root)
{
  if ( ! root)
    return TreeInfo(0, 0);

  TreeInfo linfo = doDiameterOfBinaryTree(root->left);
  TreeInfo rinfo = doDiameterOfBinaryTree(root->right);
  TreeInfo ret;
  ret.height = max(linfo.height, rinfo.height) + 1;
  ret.diameter = max(max(linfo.diameter, rinfo.diameter), linfo.height+rinfo.height);
  std::cout << "val:" << root->val << ",height:" << ret.height << ",diameter:" << ret.diameter << std::endl;
  return ret;
}

int diameterOfBinaryTree(TreeNode* root) 
{
  TreeInfo ret = doDiameterOfBinaryTree(root);
  return ret.diameter;
}

int main()
{
  vector<int> nums = {1, 2, 3, 4, 5, null, null};
  TreeNode* root = generateTree(nums);
  showTree(root);
  std::cout << diameterOfBinaryTree(root) << std::endl;
  return 0;
}
