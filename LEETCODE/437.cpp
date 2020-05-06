#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
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
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        int ret = 0;
        // 路径中不包括root
        ret += pathSum(root->left, sum);
        ret += pathSum(root->right, sum);

        // 路径中包括root
        ret += pathSumIncludeRoot(root, sum);
        return ret;
    }
    
    int pathSumIncludeRoot(TreeNode* root, int sum) {
        if (root == nullptr) return 0;
        int ret = 0;
        if (root->val == sum) ++ret;
        ret += pathSumIncludeRoot(root->left, sum-root->val);
        ret += pathSumIncludeRoot(root->right, sum-root->val);
        return ret;
    }
};

int main() {
    return 0;
}

