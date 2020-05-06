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
    TreeNode* increasingBST(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* new_root = nullptr;
        TreeNode* new_tail = nullptr;
        std::stack<TreeNode*> st;
        st.push(root);
        while (! st.empty()) {
            auto curr = st.top();
            if (curr->left != nullptr) {
                st.push(curr->left);
                continue;
            }

            while (curr->right == nullptr) {
                append(new_root, new_tail, curr);
                st.pop();

                if (st.empty()) {
                    break;
                }
                curr = st.top();
            }

            if (st.empty()) {
                break;
            } else {
                auto next = curr->right;
                append(new_root, new_tail, curr);
                st.pop();
                st.push(next);
            }
        }
        new_tail->left = nullptr;
        new_tail->right = nullptr;
        return new_root;
    }
    
    void append(TreeNode*& new_root, TreeNode*& new_tail, TreeNode* curr) {
        if (new_root == nullptr) {
            new_root = curr;
            new_tail = curr;
            return;
        }
        new_tail->right = curr;
        new_tail->left = nullptr;
        new_tail = curr;
    }
};

int main() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    
    TreeNode* new_root = Solution().increasingBST(root);
    while (new_root != nullptr) {
        std::cout << new_root->val << std::endl;
        new_root = new_root->right;
    }
    return 0;
}

