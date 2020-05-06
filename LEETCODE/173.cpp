#include <iostream>
#include <string>
#include <cassert>
#include "tree.h"
#include "util.h"
using std::string;

class BSTIterator {
  public:

    BSTIterator(TreeNode *root) 
    {
      root_node_ = root;
      curr_node_ = farNode(root_node_, LEFT);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() 
    {
      return curr_node_ != NULL;
    }

    /** @return the next smallest number */
    int next() 
    {
      if (!curr_node_)
        return NULL;

      int ret = curr_node_->val; 

      // current node has right child
      if (curr_node_->right)
      {
        curr_node_ = farNode(curr_node_->right, LEFT);
        return ret;
      }

      // current node withour right child
      vector<TreeNode*> nodes;
      bool has_path  = treePath(root_node_, curr_node_, nodes);
      assert(has_path != false);
      if (nodes.size() == 1)
      {
        curr_node_ = NULL;
        return ret;
      }

      // curr_node is left child 
      if (nodes[nodes.size()-2]->left == curr_node_)
      {
        curr_node_ = nodes[nodes.size()-2];
        return ret;
      }

      // curr_node is right child
      TreeNode* tmp = NULL;
      for (int i=nodes.size()-2; i>=0; --i)
      {
        TreeNode* child = nodes[i+1];
        if (nodes[i]->right && nodes[i]->left == child)
        {
          tmp = nodes[i];
          break;
        }
      }
      curr_node_ = tmp;
      return ret;
    }

  private:
    
    
  private:
    TreeNode* root_node_;
    TreeNode* curr_node_;
};


int main()
{
  /*
  vector<int> nums = {41,37,44,24,39,42,48,1,35,38,40,null,43,46,49,0,2,30,36,null,null,null,null,null,null,45,47,null,null,null,null,null,4,29,32,null,null,null,null,null,null,3,9,26,null,31,34,null,null,7,11,25,27,null,null,33,null,6,8,10,16,null,null,null,28,null,null,5,null,null,null,null,null,15,19,null,null,null,null,12,null,18,20,null,13,17,null,null,22,null,14,null,null,21,23};
  // vector<int> nums = {1, 1, 2, 3, 4, 0, 6, 7};
  */
  // vector<int> nums = {5, 3, 7, 1, null, 6, null};
  vector<int> nums = {3, 5, 7, 33, 12, 9, 0, 1, 13, 22, 5, 4, 2, 89};
  TreeNode* root = createTree(nums);
  std::cout << stringify(nums) << std::endl;
  
  vector<int> nums1;
  inorderTraversal(root, nums1);
  std::cout << stringify(nums) << std::endl;

  BSTIterator tit(root);
  while (tit.hasNext())
    std::cout << tit.next() << " ";
  std::cout << std::endl;

  return 0;
}
