#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode** r = &root;
        TreeNode** curr = r;
        while (*curr != NULL) {
            TreeNode* entry = *curr;
            if (val < entry->val) {
                curr = &(entry->left);
            } else {
                curr = &(entry->right);
            }
        }
        *curr = new TreeNode(val);
        return *r;
    }
};

int main() {
}
