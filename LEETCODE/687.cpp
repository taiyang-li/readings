#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        int path_with_root = helper(root->left, root->val) + helper(root->right, root->val);
        return std::max(path_with_root, std::max(longestUnivaluePath(root->left), longestUnivaluePath(root->right)));
    }

    int helper(TreeNode* root, int val) {
        if (root == NULL || root ->val != val) {
            return 0;
        }
        return 1 + std::max(helper(root->left, val), helper(root->right, val));
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(5);
    std::cout << Solution().longestUnivaluePath(root) << std::endl;
    return 0;
}
