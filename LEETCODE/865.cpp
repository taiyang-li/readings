#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        std::map<TreeNode*, int>().swap(_heights);
        heightHelper(root);
        return subtreeWithAllDeepestHelper(root);
    }

    TreeNode* subtreeWithAllDeepestHelper(TreeNode* root) {
        int left_height = _heights[root->left];
        int right_height = _heights[root->right];
        if (left_height == right_height) {
            return root;
        } else if (left_height > right_height) {
            return subtreeWithAllDeepestHelper(root->left);
        } else {
            return subtreeWithAllDeepestHelper(root->right);
        }
    }

    int heightHelper(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int left_height = heightHelper(root->left);
        int right_height = heightHelper(root->right);
        int ret = 1+std::max(left_height, right_height);
        _heights[root] = ret;
        return ret;
    }

protected:
    std::map<TreeNode*, int> _heights;
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    auto ret = Solution().subtreeWithAllDeepest(root);
    std::cout  << ret->val << std::endl;
    return 0;
}
