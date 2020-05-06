#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <stack>
#include <cstdint>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        if (root == NULL) {
            return vector<int>();
        }

        int curr = 0;
        int prev = INT_MIN;
        int max_count = 0;
        int curr_count = 0;
        TreeNode* p = root;
        vector<int> models;
        stack<TreeNode*> s;
        while (p != NULL || ! s.empty()) {
            while (p != NULL) {
                s.push(p);
                p = p->left;
            }

            if (! s.empty()) {
                p = s.top();
                s.pop();
                curr = p->val;
                p = p->right;

                if (curr != prev) {
                    if (curr_count >= max_count && curr_count > 0) {
                        if (curr_count > max_count) {
                            max_count = curr_count;
                            models.clear();
                        }  
                        models.push_back(prev);
                    }
                    curr_count = 0;
                }
                curr_count++;
                prev = curr;
            }
        }

        if (curr_count >= max_count && curr_count > 0) {
            if (curr_count > max_count) {
                max_count = curr_count;
                models.clear();
            }  
            models.push_back(prev);
        }
        return models;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(2);

    Solution solution;
    vector<int> ret = solution.findMode(root);
    for (auto x : ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
    
