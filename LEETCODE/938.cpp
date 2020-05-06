#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
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
    int rangeSumBST(TreeNode* root, int L, int R) {
        if (root == nullptr) {
            return 0;
        }

        if (root->val >= L && root->val <= R) {
            return root->val + rangeSumBST(root->left, L, root->val-1) + rangeSumBST(root->right, root->val+1, R);
        } else if (root->val < L) {
            return rangeSumBST(root->right, L, R);
        } else {
            return rangeSumBST(root->left, L, R);
        }
    }
};
int main() {
    return 0;
}

