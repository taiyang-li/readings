#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if (root == NULL) {
            return vector<int>();
        }

        _frequency_by_sum.clear();
        _sum_by_frequency.clear();
        doFindFrequentTreeSum(root);
        auto most_frequency_sums = _sum_by_frequency.rbegin()->second;
        return vector<int>(most_frequency_sums.begin(), most_frequency_sums.end());
    }

    int doFindFrequentTreeSum(TreeNode* root) {
        int sum = root->val;
        if (root->left) {
            sum += doFindFrequentTreeSum(root->left);
        }
        if (root->right) {
            sum += doFindFrequentTreeSum(root->right);
        }
        incr_frequency(sum);
        return sum;
    }

    inline void incr_frequency(int sum) {
        if (_frequency_by_sum.count(sum) > 0) {
            _sum_by_frequency[_frequency_by_sum[sum]].erase(sum);
        }
        _frequency_by_sum[sum]++;
        _sum_by_frequency[_frequency_by_sum[sum]].insert(sum);
    }
private:
    std::map<int, int> _frequency_by_sum;
    std::map<int, set<int> > _sum_by_frequency;
        
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(-5);
    auto ret = Solution().findFrequentTreeSum(root);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
