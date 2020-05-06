#include <iostream>
#include <cstddef>
#include <queue>

template <class T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& v) : val(v), left(nullptr), right(nullptr) {}
};

template <class T>
bool is_complete_binary_tree(TreeNode<T>* root) {
    if (root == nullptr) {
        return true;
    }

    std::queue<TreeNode<T>* > q;
    q.push(root);
    bool flag = false;
    while (! q.empty()) {
        auto curr = q.front();
        q.pop();
        if (curr->left != nullptr && curr->right != nullptr) {
            q.push(curr->left);
            q.push(curr->right);
            continue;
        }
        if (flag) {
            if (curr->left != nullptr || curr->right != nullptr) {
                return false;
            }
        } else {
            if (curr->left == nullptr && curr->right != nullptr) {
                return false;
            }
            flag = true;
        }
    }
}

int main() {
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    // root->left->right = new TreeNode<int>(5);
    root->right->left = new TreeNode<int>(6);
    
    std::cout << is_complete_binary_tree(root) << std::endl;
    return 0;
}
