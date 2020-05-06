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
    vector<string> fizzBuzz(int n) {
        if (n <=0 ) {
            return std::vector<std::string>();
        }
        std::vector<std::string> ret(n, std::string());
        for (int i=1; i<=n; ++i) {
            ret[i-1] = to_string(i);
        }
        return ret;
    }
    
    inline std::string to_string(int n) {
        if (n % 3 == 0 && n % 5 == 0) {
            return "FizzBuzz";
        } else if (n % 3 == 0) {
            return "Fizz";
        } else if (n % 5 == 0) {
            return "Buzz";
        } else {
            return std::to_string(n);
        }
    }
};

int main() {
    auto ret = Solution().fizzBuzz(15);
    for (auto x : ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
