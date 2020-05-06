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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr && t1 == nullptr) {
            return nullptr;
        }
        
        int val = 0;
        if (t1 != nullptr) {
            val += t1->val;
        }
        if (t2 != nullptr) {
            val += t2->val;
        }
        TreeNode* ret = new TreeNode(val);
        ret->left = mergeTrees(t1 ? t1->left : nullptr, t2 ? t2->left : nullptr);
        ret->right = mergeTrees(t1 ? t1->right: nullptr, t2 ? t2->right : nullptr);
        return ret;
    }
};

int main() {
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    
    TreeNode* root2 = new TreeNode(2);
    root2->right = new TreeNode(3);

    TreeNode* root = Solution().mergeTrees(root1, root2);
    return 0;
}

