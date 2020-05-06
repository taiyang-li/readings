
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeNodeWithIndex {
    TreeNode* node;
    int index;
    TreeNodeWithIndex(TreeNode* n = NULL, int i = 0): node(n), index(i) {}
};

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        bool has_next = true;
        int max_width = 1;
        int start_index = 0;
        int end_index = 0;
        TreeNodeWithIndex curr;
        std::queue<TreeNodeWithIndex> q;
        std::vector<TreeNodeWithIndex> v;
        q.push(TreeNodeWithIndex(root, 0));
        while (1) {
            while (! q.empty()) {
                curr = q.front();
                q.pop();
                if (curr.node->left) {
                    v.push_back(TreeNodeWithIndex(curr.node->left, 2 * curr.index + 1));
                } 
                if (curr.node->right) {
                    v.push_back(TreeNodeWithIndex(curr.node->right, 2 * curr.index + 2));
                }
            }

            has_next = ! v.empty();
            if (! has_next) {
                break;
            } 
            max_width = std::max(max_width, v.rbegin()->index - v.begin()->index + 1);
            for (auto x : v) {
                q.push(x);
            }
            v.clear();
        }
        return max_width;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(3);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(9);
    /*
    TreeNode* root = new TreeNode(0);
    TreeNode* tmp = root;
    for (int i=0; i<20; ++i) {
        tmp->right = new TreeNode(0);
        tmp = tmp->right;
    }
    */
    std::cout << Solution().widthOfBinaryTree(root) << std::endl;
    return 0;
}
