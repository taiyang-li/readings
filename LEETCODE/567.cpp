#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Solution {
public:
    typedef std::map<char, int> Composition;
    bool checkInclusion(const string& s1, const string& s2) {
        if (s1.size() > s2.size()) {
            return false;
        }
        if (s1.empty()) {
            return true;
        }

        Composition c1;
        for (auto ch : s1) {
            c1[ch]++;
        }
        Composition c2;
        for (size_t i=0; i<s1.size(); ++i) {
            c2[s2[i]]++;
        }
        if (c1 == c2) {
            return true;
        }

        for (size_t i=s1.size(); i<s2.size(); ++i) {
            update_composition(s2[i-s1.size()], s2[i], c2);
            if (c1 == c2) {
                return true;
            }
        }
        return false;
    }

    void update_composition(char del, char add, Composition& c) {
        if (del == add) {
            return;
        }
        
        if (c[del] == 1) {
            c.erase(del);
        } else {
            c[del]--;
        }
        c[add]++;
    }

};

int main() {
    std::cout << Solution().checkInclusion("ab", "eidbaooo") << std::endl;
    std::cout << Solution().checkInclusion("ab", "eidboaoo") << std::endl;
    return 0;
}
