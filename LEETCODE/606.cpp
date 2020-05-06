#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    std::string tree2str(TreeNode* t) {
        if (t == NULL) {
            return "";
        }
        std::string ret;
        ret.append(std::to_string(t->val));
        std::string left_ret = tree2str(t->left);
        std::string right_ret = tree2str(t->right);
        if (t->right != NULL) {
            ret.append("(");
            ret.append(left_ret);
            ret.append(")");
            ret.append("(");
            ret.append(right_ret);
            ret.append(")");
        } else if (t->left != NULL) {
            ret.append("(");
            ret.append(left_ret);
            ret.append(")");
        } 
        return ret;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->right = new TreeNode(3);
    std::cout << Solution().tree2str(root) << std::endl;
    return 0;
}
