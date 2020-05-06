#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int longest_palindrome(const std::string& s) {
    if (s.size() < 1) {
        return s.size();
    }

    const int n = s.size();
    std::string ns(2*n+1, '#');
    for (int i=0; i<n; ++i) {
        ns[2*i+1] = s[i];
    }

    int max_len = 0;
    int mx = 0;
    int id = 0; 
    std::vector<int> tb(2*n+1, 0);
    for (int i=1; i<2*n+1; ++i) {
        if (i < mx) {
            tb[i] = std::min(mx - i, tb[2*id-i]);
        } else {
            tb[i] = 1;
        }
        
        while (i - tb[i] >= 0 && i + tb[i] < 2*n+1 && ns[i-tb[i]] == ns[i+tb[i]]) {
            ++tb[i];
        }

        if (i + tb[i] > mx) {
            id = i;
            mx = i + tb[i];
        }

        if (tb[i]-1 > max_len) {
            max_len = tb[i]-1;
        }
    }
    return max_len;
}

int main() {
    std::cout << longest_palindrome("1212134") << std::endl;
    return 0;
}
