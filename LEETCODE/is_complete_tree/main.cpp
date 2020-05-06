#include <iostream>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool is_complete_tree(TreeNode* root) {
    bool has_nochild = false;
    std::queue<TreeNode*> que;
    que.push(root);
    while (! que.empty()) {
        auto curr = que.front();
        que.pop();

        if (has_nochild && (curr->left != nullptr || curr->right != nullptr)) {
            return false;
        }

        if (curr->left != nullptr && curr->right != nullptr) {
            que.push(curr->left);
            que.push(curr->right);
        } else if (curr->left != nullptr && curr->right == nullptr) {
            que.push(curr->left);
            has_nochild = true;
        } else if (curr->left == nullptr && curr->right != nullptr) {
            return false;
        } else {
            has_nochild = true;
        }
    }
    return true;
}

int main() {
    int i = 0;
    TreeNode* root = new TreeNode(i++);
    root->left = new TreeNode(i++);
    root->right = new TreeNode(i++);
    root->left->left = new TreeNode(i++);
    root->left->right= new TreeNode(i++);
    root->right->right = new TreeNode(i++);
    std::cout << is_complete_tree(root) << std::endl;
    return 0;
}
