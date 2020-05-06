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
    int longestPalindrome(const string& s) {
        int counts[128] = {0};
        for (auto ch : s) {
            counts[int(ch)]++;
        }

        int ret = 0;
        int have_odd_count = false;
        for (int i=0; i<128; ++i) {
            if (counts[i] == 0) {
                continue;
            }

            if (counts[i] % 2 == 0) {
                ret += counts[i];
            } else {
                ret += counts[i]-1;
                have_odd_count = true;
            }
        }
        if (have_odd_count) {
            ret++;
        }
        return ret;
    }
};

int main() {
    // std::cout << Solution().longestPalindrome("abccccdd") << std::endl;
    std::cout << Solution().longestPalindrome("civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth") << std::endl;
    return 0;
}
