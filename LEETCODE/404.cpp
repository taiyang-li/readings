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
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int ret = 0;
        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            ret += root->left->val;
            ret += sumOfLeftLeaves(root->right);
        } else {
            ret += sumOfLeftLeaves(root->left);
            ret += sumOfLeftLeaves(root->right);
        }
        return ret;
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    std::cout << Solution().sumOfLeftLeaves(root) << std::endl;
    return 0;
}
