#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
using std::vector;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        std::map<int, int>().swap(_size_by_val);
        get_size_by_val(root);
        int n = _size_by_val[root->val];
        return do_flip_match_voyage(root, voyage, 0, n);
    }

    std::vector<int> do_flip_match_voyage(TreeNode* root, vector<int>& voyage, int start, int len) {
        if (root->val != voyage[start]) {
            return {-1};
        }
        int left_size = root->left != NULL ? _size_by_val[root->left->val] : 0;
        int right_size = root->right != NULL ? _size_by_val[root->right->val] : 0;
        std::vector<int> left_ret;
        std::vector<int> right_ret;
        std::vector<int> ret;
        if (left_size == 0 && right_size == 0) {
            return {};
        } else if (left_size == 0) {
            left_ret = do_flip_match_voyage(root->right, voyage, start+1, right_size);
            return left_ret;
        } else if (right_size == 0) {
            right_ret = do_flip_match_voyage(root->left, voyage, start+1, left_size);
            return right_ret;
        }
        else {
            if (root->left->val == voyage[start+1]) {
                left_ret = do_flip_match_voyage(root->left, voyage, start+1, left_size);
                right_ret = do_flip_match_voyage(root->right, voyage, start+1+left_size, right_size);
            } else {
                ret.push_back(root->val);
                left_ret = do_flip_match_voyage(root->left, voyage, start+1+right_size, left_size);
                right_ret = do_flip_match_voyage(root->right, voyage, start+1, right_size);
            }

            if (left_ret == _invalid_result || right_ret == _invalid_result) {
                return {-1};
            } else {
                ret.insert(ret.end(), left_ret.begin(), left_ret.end());
                ret.insert(ret.end(), right_ret.begin(), right_ret.end());
                return ret;
            }
        }
    }

    void get_size_by_val(TreeNode* root) {
        if (root == NULL) {
            return;
        }

        get_size_by_val(root->left);
        get_size_by_val(root->right);
        _size_by_val[root->val] = 1 + (root->left != NULL ? _size_by_val[root->left->val] : 0) +
            (root->right != NULL ? _size_by_val[root->right->val] : 0);
    }

    inline bool is_invalid(std::vector<int>& result) {
        return result.size() == 1 && result[0] == -1;
    }
protected:
    std::map<int, int> _size_by_val;
    static const std::vector<int> _invalid_result;
};

const std::vector<int> Solution::_invalid_result = {-1};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    std::vector<int> voyage = {1,2,3};
    auto ret = Solution().flipMatchVoyage(root, voyage);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
