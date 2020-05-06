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
    int minDiffInBST(TreeNode* root) {
        int ret = INT_MAX;
        TreeNode* prev = nullptr;
        std::stack<TreeNode*> st;
        st.push(root);
        while (! st.empty()) {
            auto curr = st.top();
            if (curr->left != nullptr) {
                st.push(curr->left);
                continue;
            }

            while (curr->right == nullptr) {
                // 计算差异
                if (prev != nullptr) {
                    ret = std::min(ret, curr->val-prev->val);
                }
                prev = curr;
                
                st.pop();
                if (st.empty()) {
                    return ret;
                }
                curr = st.top();
            }
            // 计算差异
            if (prev != nullptr) {
                ret = std::min(ret, curr->val-prev->val);
            }
            prev = curr;
            st.pop();
            st.push(curr->right);
        }
        return ret;
    }
};

int main() {
    return 0;
}

