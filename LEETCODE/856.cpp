#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <stack>
using namespace std;

class Solution {
public:
    int scoreOfParentheses(const string& S) {
        auto distances = calculatePairIndexes(S);
        return helper(S, 0, int(S.size()), distances);
    }

    int helper(const string& S, int start, int len, std::map<int, int>& pair_indexes) {
        string s = S.substr(start, len);
        if (s.empty()) {
            return 0;
        } 
        if (s == "()") {
            return 1;
        }

        int pair_index = pair_indexes[start];
        if (pair_index - start + 1 == len) {
            return 2 * helper(S, start+1, pair_index-start-1, pair_indexes);
        } else {
            return helper(S, start, pair_index-start+1, pair_indexes) + 
                helper(S, pair_index+1, len-(pair_index-start+1), pair_indexes);
        }
    }

    std::map<int, int> calculatePairIndexes(const string& S) {
        std::map<int, int> pair_indexes;
        std::stack<int> st;
        for (size_t i=0; i<S.size(); ++i) {
            if (S[i] == '(') {
                st.push(i);
            } else {
                auto j = st.top();
                pair_indexes[j] = i;
                st.pop();
            }
        }
        return pair_indexes;
    }
};

int main() {
    std::cout << Solution().scoreOfParentheses("()") << std::endl;
    std::cout << Solution().scoreOfParentheses("(())") << std::endl;
    std::cout << Solution().scoreOfParentheses("()()") << std::endl;
    std::cout << Solution().scoreOfParentheses("()()()") << std::endl;
    std::cout << Solution().scoreOfParentheses("(()(()))") << std::endl;
    return 0;
}
