#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (root == NULL) {
            return -1;
        }
        return findMinimumValueGreaterThan(root, root->val);
    }

    int findMinimumValueGreaterThan(TreeNode* root, int target) {
        if (root == NULL) {
            return -1;
        }

        if (root->val > target) {
            return root->val;
        }

        int left_ret = findMinimumValueGreaterThan(root->left, target);
        int right_ret = findMinimumValueGreaterThan(root->right, target);

        if (left_ret == -1) {
            return right_ret;
        } else {
            if (right_ret == -1) {
                return left_ret;
            } else {
                return min(left_ret, right_ret);
            }
        }
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(5);
    std::cout << solution.findSecondMinimumValue(root) << std::endl;
    return 0;
}
