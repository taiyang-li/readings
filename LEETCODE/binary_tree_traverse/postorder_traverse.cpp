#include "tree_node.h"
#include <stack>
#include <iostream>

template <class T>
void postorder_traverse(TreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }

    std::stack<TreeNode<T>* > s;
    s.push(root);
    while (! s.empty()) {
        auto curr = s.top();
        if (curr->left != nullptr || curr->right != nullptr) {
            if (curr->right != nullptr) {
                s.push(curr->right);
            } 
            if (curr->left != nullptr) {
                s.push(curr->left);
            }
        } else {
            std::cout << curr->val << std::endl;
            s.pop();

            while (! s.empty() && s.top()->right == curr) {
                curr = s.top();
                std::cout << curr->val << std::endl;
                s.pop();
            }
        }
    }
}

int main() {
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->left = new TreeNode<int>(6);
    root->right->right = new TreeNode<int>(7);
    
    postorder_traverse(root);
    return 0;
}
