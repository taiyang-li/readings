#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    static const vector<string> morse_codes;

    inline void word_to_morse_code(const string& word, string& morse_code) {
        morse_code.clear();
        morse_code.reserve(word.size() * 4);
        for (auto ch : word) {
            morse_code.append(morse_codes[ch - 'a']);
        }
    }

    int uniqueMorseRepresentations(vector<string>& words) {
        unordered_set<string> morse_code_set;
        string morse_code;
        for (const auto& word: words) {
            word_to_morse_code(word, morse_code);
            morse_code_set.insert(morse_code);
        }
        return morse_code_set.size();
    }
};

const vector<string> Solution::morse_codes = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

int main() {
    Solution solution;
    vector<string> words = {"gin", "zen", "gig", "msg"};
    std::cout << solution.uniqueMorseRepresentations(words) << std::endl;
    return 0;
}
