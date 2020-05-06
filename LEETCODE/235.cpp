#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include "tree.h"
using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL || p == NULL || q == NULL) return NULL;
        int ps = (p->val > root->val) ? 1 : ((p->val == root->val) ? 0 : -1);
        int qs = (q->val > root->val) ? 1 : ((q->val == root->val) ? 0 : -1);
        if (ps * qs <= 0) {
            return root;
        }
        return ps > 0 ? lowestCommonAncestor(root->right, p, q) : lowestCommonAncestor(root->left, p, q);
    }
};

int main() {
    std::vector<int> nums = {6,2,8,0,4,7,9,null,null,3,5};
    TreeNode* root = generateTree(nums);
    auto ret = Solution().lowestCommonAncestor(root, root->left, root->right);
    std::cout << ret->val << std::endl;
    return 0;
}
