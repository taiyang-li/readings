#include <cstdio>
#include <cstddef>

template <class T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& v) : val(v), left(nullptr), right(nullptr) {}
};

