#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include "tree.h"

class BSTIterator {
  public:

    BSTIterator(TreeNode *root) 
    {
      current_ = root;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() 
    {
      return current_ || ! stack_.empty();
    }

    /** @return the next smallest number */
    int next() 
    {
      while (current_)
      {
        stack_.push(current_);
        current_ = current_->left;
      }
      current_ = stack_.top();
      stack_.pop();
      int ret = current_->val;
      current_ = current_->right;
      return ret;
    }

  private:
    TreeNode* current_;
    std::stack<TreeNode*> stack_;
};

