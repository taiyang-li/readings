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
        bool findTarget(TreeNode* root, int k) {
            std::stack<TreeNode*> st;
            std::unordered_set<int> needed;
            st.push(root);
            while (! st.empty()) {
                auto curr = st.top();
                if (curr->left != nullptr) {
                    st.push(curr->left);
                    continue;
                }

                while (curr->right == nullptr) {
                    if (needed.count(curr->val) > 0) {
                        return true;
                    } else {
                        needed.insert(k - curr->val);
                    }

                    st.pop();
                    if (st.empty()) {
                        return false;
                    }
                    curr = st.top();
                }
                if (needed.count(curr->val) > 0) {
                    return true;
                } else {
                    needed.insert(k - curr->val);
                }
                st.pop();
                st.push(curr->right);
            }
            return false;
        }
}; 
int main() {
    return 0;
}

