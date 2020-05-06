#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    struct CharFrequency {
        char c;
        uint32_t freq;
    };

    class CmpByFreq {
        public:
        bool operator()(const CharFrequency& left, const CharFrequency& right) {
            if (left.freq < right.freq) {
                return false;
            } else if (left.freq == right.freq) {
                return left.c > right.c;
            } else {
                return true;
            }
        }
    };
    
    string frequencySort(const string& s) {
       CharFrequency char_freqs[128];
       for (size_t i=0; i<128; ++i) {
           char_freqs[i].c = (char)i;
           char_freqs[i].freq = 0;
       } 
       for (auto c : s) {
           char_freqs[c].freq++;
       }
       sort(char_freqs, char_freqs+128, CmpByFreq());

       string ret;
       ret.reserve(s.size());
       for (size_t i=0; i<128; ++i) {
           if (char_freqs[i].freq > 0) {
               ret.append(char_freqs[i].freq, char_freqs[i].c);
           }
       }
       return ret;
    }
};

int main() {
    Solution solution;
    std::cout << solution.frequencySort("Aabb") << std::endl;
    std::cout << solution.frequencySort("bbaA") << std::endl;
    return 0;
}
