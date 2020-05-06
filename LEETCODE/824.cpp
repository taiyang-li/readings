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
#include <numeric>
#include <sstream>
using std::vector;
using std::string;

class Solution {
public:
    string toGoatLatin(const string& S) {
        std::istringstream iss(S);
        int idx = 1;
        std::string word;
        std::string suffix = "a";
        std::string ret = "";
        while (! iss.eof()) {
            iss >> word;
            if (! (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || 
                    word[0] == 'o' || word[0] == 'u' || word[0] == 'A'|| 
                    word[0] == 'E' || word[0] == 'I' || word[0] == 'O' ||
                    word[0] == 'U')) {
                auto ch = word[0];
                word.erase(word.begin());
                word += ch;
            }
            word += "ma";
            word += suffix;
            if (idx > 1) {
                ret += " ";
            }
            ret += word;
            
            ++idx;
            suffix += 'a';
        }
        return ret;
    }
};

int main() {
    std::string S = "The quick brown fox jumped over the lazy dog";
    std::cout << Solution().toGoatLatin(S) << std::endl;
    return 0;
}

