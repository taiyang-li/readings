#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    std::string licenseKeyFormatting(const string& S, int K) {
        std::string s(S);
        s.erase(std::remove(s.begin(), s.end(), '-'), s.end());
        const int len = s.size();
        int head_len = (len % K == 0) ? K : len % K;
        std::string ret(s.begin(), s.begin()+head_len);
        for (int i=head_len; i<len; i += K) {
            ret.append("-");
            ret.append(s, i, K);
        }
        for (auto& ch : ret) {
            ch = ::toupper(ch);
        }
        return ret;
    }
};

int main() {
    std::string S = "ab-cdefg-hilkshpkdhge";
    int K = 4;
    std::cout << Solution().licenseKeyFormatting(S, K) << std::endl;
    return 0;
}
