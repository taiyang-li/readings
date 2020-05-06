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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        std::vector<int> leafs1;
        std::vector<int> leafs2;
        helper(root1, leafs1);
        helper(root2, leafs2);
        // std::for_each(leafs1.begin(), leafs1.end(), [](int n) {std::cout << n << std::endl;});
        // std::for_each(leafs2.begin(), leafs2.end(), [](int n) {std::cout << n << std::endl;});
        return leafs1 == leafs2;
    }

    void helper(TreeNode* root, std::vector<int>& leafs) {
        if (root == nullptr) {
            return;
        }
        
        if (root->left == nullptr && root->right == nullptr) {
            leafs.push_back(root->val);
            return;
        }

        helper(root->left, leafs);
        helper(root->right, leafs);
    }
};


int main() {
    TreeNode* root1 = new TreeNode(1);
    TreeNode* root2 = new TreeNode(2);
    std::cout << Solution().leafSimilar(root1, root2) << std::endl;
    return 0;
}

