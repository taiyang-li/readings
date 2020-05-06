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
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

enum Status {
    CAMERA,
    IN_SIGHT,
    OUT_SIGHT
};

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        _ans = 0;
        if (dfs(root) == OUT_SIGHT) {
            _ans++;
        }
        return _ans;
    }

    int dfs(TreeNode* root) {
        if (root == NULL) {
            return IN_SIGHT;
        }

        int left = dfs(root->left);
        int right = dfs(root->right);
        if (left == OUT_SIGHT || right == OUT_SIGHT) {
            _ans++;
            return CAMERA;
        } else if (left == CAMERA || right == CAMERA) {
            return IN_SIGHT;
        } else {
            return OUT_SIGHT;
        }
    }

protected:
    int _ans;
};

int main() {
    return 0;
}
