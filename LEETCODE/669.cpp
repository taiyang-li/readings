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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (root == nullptr) return nullptr;
        int val = root->val;
        if (val < L) {
            root->left = nullptr;
            return trimBST(root->right, L, R);
        } else if (val == L) {
            root->left = nullptr;
            root->right = trimBST(root->right, L, R);
            return root;
        } else if (L < val && val < R) {
            root->left = trimBST(root->left, L, R);
            root->right = trimBST(root->right, L, R);
            return root;
        } else if (val == R) {
            root->left = trimBST(root->left, L, R);
            root->right = nullptr;
            return root;
        } else {
            root->right = nullptr;
            return trimBST(root->left, L, R);
        }
    }
};

int main() {
    return 0;
}

