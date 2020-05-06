#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    bool isLongPressedName(const string& name, const string& typed) {
        const int name_len = name.size();
        const int typed_len = typed.size();
        int name_idx = 0;
        int typed_idx = 0;
        while (name_idx < name_len && typed_idx < typed_len) {
            char prev = name[name_idx];
            int count = 0;
            while (name_idx < name_len && name[name_idx] == prev) {
                name_idx++;
                count++;
            }

            while (typed_idx < typed_len && typed[typed_idx] == prev) {
                typed_idx++;
                count--;
            }
            
            if (count > 0) {
                return false;
            }
        }
        return name_idx == name_len && typed_idx == typed_len;
    }
}; 

int main() {
    std::string name = "alex";
    std::string typed = "aaaaaaaaalexxxxx";
    std::cout << Solution().isLongPressedName(name, typed) << std::endl;
    return 0;
}
