#include<iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

bool find_node(TreeNode* root, TreeNode* target) {
    if (root == nullptr || target == nullptr) {
        return false;
    }

    if (root == target) {
        return true;
    }
    return find_node(root->left, target) || find_node(root->right, target);
}


TreeNode* get_last_common_parent(TreeNode* root, TreeNode* a, TreeNode* b) {
    if (root == a || root == b) {
        return root;
    }

    if (find_node(root->left, a)) {
        if (find_node(root->left, b)) {
            return get_last_common_parent(root->left, a, b);
        } else {
            return root;
        }
    } else {
        if (find_node(root->left, b)) {
            return root;
        } else {
            return get_last_common_parent(root->right, a, b);
        }
    }
} 

int main() {
    int i = 0;
    TreeNode* root = new TreeNode(i++);
    root->left = new TreeNode(i++);
    root->right = new TreeNode(i++);
    root->left->left= new TreeNode(i++);
    root->left->right= new TreeNode(i++);
    root->right->left= new TreeNode(i++);
    root->right->right= new TreeNode(i++);
    std::cout << (get_last_common_parent(root, root->left->left, root->left->right))->val << std::endl;
    std::cout << (get_last_common_parent(root, root->left->left, root->right->right))->val << std::endl;
    return 0;
}



