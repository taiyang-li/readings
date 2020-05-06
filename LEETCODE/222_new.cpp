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
    int countNodes(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int lh = getHeight(root, true);
        return doCountNodes(root, true, lh);
    }

    int doCountNodes(TreeNode* root, bool is_left, int height) {
        if (root == NULL) {
            return 0;
        }
        int lh = is_left ? height : getHeight(root, true);
        int rh = is_left ? getHeight(root, false) : height;
        if (lh == rh) {
            return int(std::pow(2, lh)) - 1;
        }
        return 1 + doCountNodes(root->left, true, lh-1) + doCountNodes(root->right, false, rh-1);
    }

    inline int getHeight(TreeNode* root, bool is_left) {
        int ret = 0;
        TreeNode* curr = root;
        while (curr != NULL) {
            ret++;
            curr = is_left ? curr->left : curr->right;
        }
        return ret;
    }
};
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(5);
    std::cout << Solution().countNodes(root) << std::endl;
    return 0;
}
