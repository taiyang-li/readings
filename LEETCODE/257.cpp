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
    vector<string> binaryTreePaths(TreeNode* root) {
        _paths.clear();
        helper(root, "");
        return _paths;
    }

    void helper(TreeNode* root, string prefix) {
        if (root == nullptr) {
            return;
        }

        if (! prefix.empty()) {
            prefix += "->";
        } 
        prefix += std::to_string(root->val);

        if (root->left == nullptr && root->right == nullptr) {
            _paths.push_back(prefix);
            return;
        }
        helper(root->left, prefix);
        helper(root->right, prefix);
    }
    
private:
    std::vector<std::string> _paths;
};

int main() {
    return 0;
}

