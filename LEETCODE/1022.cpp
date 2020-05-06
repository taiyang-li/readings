#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
using std::vector;
using std::string;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
    public:
        int sumRootToLeaf(TreeNode* root) {
            if (root == nullptr) return 0;
            _sum = 0;
            helper(root, 0);
            return _sum;
        }

        void helper(TreeNode* root, int prefix) {
            assert(root != nullptr);
            prefix = (prefix << 1) | root->val;
            if (root->left == nullptr && root->right == nullptr) {
                _sum += prefix;
                return;
            }
            if (root->left != nullptr) {
                helper(root->left, prefix);
            }
            
            if (root->right != nullptr) {
                helper(root->right, prefix);
            }
        }
        
    private:
        int _sum;
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->left->right= new TreeNode(1);
    root->right->left= new TreeNode(0);
    root->right->right= new TreeNode(1);
    std::cout << Solution().sumRootToLeaf(root) << std::endl;
    return 0;
}

