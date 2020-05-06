#include <iostream>
#include <map>
#include <cassert>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

int count_treenode(TreeNode* root, std::map<TreeNode*, int>& count) {
    if (root == nullptr) {
        return 0;
    }
    int ret = 1;
    ret += count_treenode(root->left, count);
    ret += count_treenode(root->right, count);
    count[root] = ret;
    return ret;
}

int find_kth_in_bst(TreeNode* root, std::map<TreeNode*, int>& count, int k) {
    assert(root != nullptr && k >= 1 && k <= count[root]);

    int left_num = count[root->left];
    if (left_num == k-1) {
        return root->val;
    } else if (left_num < k-1) {
        return find_kth_in_bst(root->right, count, k-1-left_num);
    } else {
        return find_kth_in_bst(root->left, count, k);
    }
}

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right= new TreeNode(3);

    std::map<TreeNode*, int> count;
    count_treenode(root, count);
    std::cout << find_kth_in_bst(root, count, 2);
    return 0;
}

