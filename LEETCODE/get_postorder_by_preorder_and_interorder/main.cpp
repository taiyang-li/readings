#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

std::vector<int> do_get_postorder(std::vector<int>& inorder, size_t instart, size_t inlen, 
        std::vector<int>& preorder, size_t prestart, size_t prelen) {
    // std::cout << "instart:" << instart << " inlen:" << inlen << " prestart:" << prestart << " prelen:" << prelen << std::endl;
    if (inlen == 0 || prelen == 0) {
        return std::vector<int>();
    }

    int root_val = preorder[prestart];
    auto it = std::find(inorder.begin() + instart, inorder.begin() + instart + inlen, root_val);
    size_t left_len = it - (inorder.begin() + instart);
    size_t right_len = inlen - 1 - left_len;

    auto left_ret = do_get_postorder(inorder, instart, left_len, preorder, prestart+1, left_len);
    auto right_ret = do_get_postorder(inorder, instart+left_len+1, right_len, preorder, prestart+1+left_len, right_len);
    auto ret = left_ret;
    ret.insert(ret.end(), right_ret.begin(), right_ret.end());
    ret.push_back(root_val);
    return ret;
}

std::vector<int> get_postorder(std::vector<int>& inorder, std::vector<int>& preorder) {
    if (inorder.empty() || preorder.empty()) {
        return std::vector<int>();
    }
    return do_get_postorder(inorder, 0, inorder.size(), preorder, 0, preorder.size());
}

int main() {
    std::vector<int> inorder = {6, 4, 7, 1, 5};
    std::vector<int> preorder = {1, 4, 6, 7, 5};
    auto ret = get_postorder(inorder, preorder);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}

