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
    string removeOuterParentheses(const string& S) {
        std::string ret;
        std::stack<char> st;
        const int len = S.size();
        int start = 0;
        int finish = 0;
        for (int i=0; i<len; ++i) {
            if (S[i] == '(') {
                if (st.empty()) {
                    start = i;
                }
                st.push('(');
            } else {
                st.pop();
                if (st.empty()) {
                    finish = i;
                    ret += S.substr(start+1, finish-start-1);
                }
            }
        }
        return ret;
    }
};

int main() {
    return 0;
}

