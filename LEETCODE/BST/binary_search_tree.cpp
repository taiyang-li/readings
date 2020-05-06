#include <cstring>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

template <class T>
struct TreeNode {
    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(const T& v) : val(v), left(nullptr), right(nullptr) {}
};

template <class T>
class BinarySearchTree {
public:
    BinarySearchTree() : _root(nullptr) {}

    ~BinarySearchTree() {
        delete_bst_helper(_root);
        _root = nullptr;
    }

    static BinarySearchTree* create_binary_search_tree(const std::vector<T>& arr) {
        std::vector<T> arr_copy(arr.cbegin(), arr.cend());
        std::sort(arr_copy.begin(), arr_copy.end());
        for (size_t i=0; i<arr.size(); ++i) {
            if (arr[i] != arr_copy[i]) {
                return nullptr;
            }
        }
        
        BinarySearchTree* bst = new BinarySearchTree<T>();
        bst->_root = create_bst_helper(arr);
        return bst;
    }

    static void delete_binary_search_tree(BinarySearchTree<T>*& bst) {
        if (bst == nullptr) {
            return;
        }
        delete bst;
        bst = nullptr;
    }

    TreeNode<T>* insert(const T& val) {
        TreeNode<T>* parent = nullptr;
        TreeNode<T>* curr = _root;
        while (curr != nullptr) {
            parent = curr;
            if (val <= curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        TreeNode<T>* node = new TreeNode<T>(val);
        if (val <= parent->val) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        return node;
    }

    TreeNode<T>* search(const T& val) {
        TreeNode<T>* curr = _root;
        while (curr != nullptr) {
            if (val == curr->val) {
                return curr;
            } else if (val <= curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return nullptr;
    }

    size_t remove(const T& val) {
        return delete_node_helper(_root, nullptr, val);
    }

    std::string output() const {
        return output_helper(_root);
    }

private:
    static TreeNode<T>* create_bst_helper(const std::vector<T>& arr) {
        if (arr.empty()) {
            return nullptr;
        }
        size_t mid = arr.size() / 2;
        while (mid+1 < arr.size() && arr[mid] == arr[mid+1]) {
            ++mid;
        }
        TreeNode<T>* root = new TreeNode<T>(arr[mid]);
        root->left = create_bst_helper(std::vector<T>(arr.cbegin(), arr.cbegin() + mid));
        root->right = create_bst_helper(std::vector<T>(arr.cbegin() + mid + 1, arr.cend()));
        return root;
    }

    static void delete_bst_helper(TreeNode<T>* root) {
        if (root == nullptr) {
            return;
        }
        TreeNode<T>* left = root->left;
        TreeNode<T>* right = root->right;
        delete root;
        delete_bst_helper(left);
        delete_bst_helper(right);
    }

    static size_t delete_node_helper(TreeNode<T>*& root, TreeNode<T>* parent, const T& val) {
        size_t ret = 0;
        if (root == nullptr) {
            return 0;
        }
        TreeNode<T>* target = root;
        TreeNode<T>* target_parent = parent;
        while (target != nullptr && target->val != val) {
            target_parent = target;
            if (val <= target->val) {
                target = target->left;
            } else {
                target = target->right;
            }
        }
        // 情况1: 找不到目标结点
        if (target == nullptr) {
            return 0;
        }
        // 情况2: 目标节点没有左子树或右子树
        if (target->left == nullptr || target->right == nullptr){
            TreeNode<T>* child = (target->left == nullptr) ? target->right : target->left;
            if (target_parent != nullptr) {
                if (target_parent->left == target) {
                    target_parent->left = child;
                } else {
                    target_parent->right = child;
                }
            } else {
                // 说明删除的是根节点，对root重新赋值
                root = child;
            }
            // 左子树中可能含有值为val的结点
            if (target->left != nullptr) {
                ret += delete_node_helper(target->left, target_parent, val);
            }
            delete target;
            ++ret;
            return ret;
        } 
        // 情况4: 目标结点既有左子树，又有右字数
        else {
            TreeNode<T>* max_node = find_max(target->left);
            if (max_node->val != target->val) {
                std::swap(target->val, max_node->val);
                ret += delete_node_helper(target->left, target, val);
            } else {
                ret += delete_node_helper(target->left, target, val);
                ret += delete_node_helper(target, target_parent, val);
            }
            return ret;
        }
    }

    static TreeNode<T>* find_max(TreeNode<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode<T>* curr = root;
        while (curr->right != nullptr) {
            curr = curr->right;
        }
        return curr;
    }

    static TreeNode<T>* find_min(TreeNode<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode<T>* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        return curr;
    }

    static std::string output_helper(TreeNode<T>* root) {
        if (root == nullptr) {
            return std::string();
        }
        std::ostringstream oss;
        oss << output_helper(root->left);
        oss << " " << root->val << " "; 
        oss << output_helper(root->right);
        return oss.str();
    }

protected:
    TreeNode<T>* _root;
};

int main() {
    // check create_binary_search_tree
    std::vector<int> arr = {1,2,3,4,5,6,7,8,9,10};
    BinarySearchTree<int>* bst = BinarySearchTree<int>::create_binary_search_tree(arr);
    std::cout << bst->output() << std::endl;

    // check search
    for (int i=1; i<=10; ++i) {
        auto tmp = bst->search(i);
        assert(tmp != nullptr && tmp->val == i);
    }

    // check insert
    for (int i=11; i<=20; ++i) {
        auto tmp = bst->insert(i);
        assert(tmp != nullptr && tmp->val == i);

        auto tmp1 = bst->search(i);
        assert(tmp == tmp1);
    }
    std::cout << bst->output() << std::endl;

    // check duplicate insert
    for (int i=11; i<=20; ++i) {
        auto tmp = bst->insert(i);
        assert(tmp != nullptr && tmp->val == i);
    }
    std::cout << bst->output() << std::endl;

    // check remove duplicate values
    for (int i=11; i<=20; ++i) {
        auto tmp = bst->remove(i);
        assert(tmp == 2);
    }
    std::cout << bst->output() << std::endl;

    // check delete_binary_search_tree
    BinarySearchTree<int>::delete_binary_search_tree(bst);

    return 0;
}
