#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(const string& s) {
        string s1;
        s1.append("[");
        s1.append(s);
        s1.append("]");

        size_t pos = 0;
        std::stack<std::string> st;
        while (pos < s1.size()) {
            if (s1[pos] == '[') {
                ++pos;
                size_t start = pos;
                for (; pos < s1.size() && s1[pos] != '[' && s1[pos] != ']'; ++pos);
                st.push("[");
                st.push(s1.substr(start, pos-start));
            } else if (s1[pos] == ']') {
                const auto& encode = st.top();
                std::string decode = flatDecodeString(encode);
                st.pop();
                st.pop();
                if (st.empty()) {
                    st.push(decode);
                } else {
                    st.top().append(decode);
                }
                ++pos;
            } else {
                if (::isalpha(s1[pos])) {
                    st.top() += "1";
                }
                st.top() += s1[pos];
                ++pos;
            }
        }
        return st.top();
    }

    string flatDecodeString(const string& s) {
        if (s.empty()) {
            return "";
        }
        // parse times
        int times = 1;
        size_t begin = 0;
        size_t end = 0;
        for (begin=0; begin<s.size() && ! ::isalpha(s[begin]); ++begin);
        if (begin > 0) {
            times = atoi(s.substr(0, begin).c_str());
        }
        for (end=begin; end<s.size() && ::isalpha(s[end]); ++end);

        std::string ret;
        while (times--) {
            ret.append(s, begin, end-begin);
        }
        ret.append(flatDecodeString(s.substr(end)));
        return ret;
    }
};

int main() {
    // std::cout << Solution().flatDecodeString("2aa3bc") << std::endl;
    // std::cout << Solution().flatDecodeString("aa3bc") << std::endl;
    // std::cout << Solution().decodeString("3[a]2[bc]") << std::endl;
    std::cout << Solution().decodeString("2[abc]3[cd]ef") << std::endl;
    return 0;
}
