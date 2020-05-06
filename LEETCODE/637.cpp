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
#include <queue>
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
    vector<double> averageOfLevels(TreeNode* root) {
        std::vector<double> ret;
        int count = 0;
        int64_t sum = 0;
        std::queue<TreeNode*> que;
        que.push(root);
        que.push(nullptr);
        while (! que.empty()) {
            auto curr = que.front();
            que.pop();
            if (curr != nullptr) {
                ++count;
                sum += curr->val;
                if (curr->left != nullptr) que.push(curr->left);
                if (curr->right != nullptr) que.push(curr->right);
            } else {
                ret.push_back(sum/(double)count);
                sum = 0;
                count = 0;
                if (! que.empty()) {
                    que.push(nullptr);
                }
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

