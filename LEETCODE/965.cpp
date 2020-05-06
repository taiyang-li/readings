#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
#include <vector>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        if (root == NULL) return true;

        if (root->left != NULL && root->val != root->left->val) return false;
        if (root->right != NULL && root->val != root->right->val) return false;

        return isUnivalTree(root->left) && isUnivalTree(root->right);
    }
}; 

int main() {
    return 0;
}
