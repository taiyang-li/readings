#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <cmath>
#include <set>
#include <stack>
#include <iostream>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct NodeState {
    int parent;
    int depth;
    
    NodeState(int p, int d) : parent(p), depth(d) {}
};

class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        build_states(root);
        auto it_x = _states_by_node.find(x);
        auto it_y = _states_by_node.find(y);
        return it_x != _states_by_node.end() && it_y != _states_by_node.end() && 
            it_x->second.parent != it_y->second.parent && it_x->second.depth == it_y->second.depth;
    }

    void build_states(TreeNode* root) {
        _states_by_node.clear();
        do_build_states(root, 0);
    }

    void do_build_states(TreeNode* root, int depth) {
        if (root == NULL) return;

        int val = root->val;
        if (root->left != NULL) {
            _states_by_node.insert(std::make_pair(root->left->val, NodeState(val, depth+1)));
            do_build_states(root->left, depth+1);
        }
        if (root->right != NULL) {
            _states_by_node.insert(std::make_pair(root->right->val, NodeState(val, depth+1)));
            do_build_states(root->right, depth+1);
        }
    }

protected:
    std::map<int, NodeState> _states_by_node;
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(4);

    Solution().build_states(root);
    return 0;
}
