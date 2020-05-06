#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
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
    int findTilt(TreeNode* root) {
        _tree_sums.clear();
        _tree_sums[nullptr] = 0;
        tree_sum(root);
        return tree_tilt(root);
    }
    
    int tree_tilt(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int root_tilt = std::abs(_tree_sums[root->left] - _tree_sums[root->right]);
        int left_tilt = tree_tilt(root->left);
        int right_tilt = tree_tilt(root->right);
        return root_tilt + left_tilt + right_tilt;
    }

    int tree_sum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_sum = tree_sum(root->left);
        int right_sum = tree_sum(root->right);
        _tree_sums[root] = root->val + left_sum + right_sum;
        return root->val + left_sum + right_sum;
    }
        
private:
    std::unordered_map<TreeNode*, int> _tree_sums;
};

int main() {
    return 0;
}

