#include <string>
#include <iostream>

std::string get_shorttest_cover_substring(const std::string& str) {
    if (str.size() <= 1) {
        return str;
    }

    size_t dst_map[128] = {0};
    size_t dst_len = 0;
    for (auto ch: str) {
        if (dst_map[ch] == 0) {
            ++dst_len;
        }
        dst_map[ch] = 1;
    }

    size_t begin = 0;
    size_t end = 0;
    size_t found = 0;
    size_t min_len = str.size();
    size_t min_begin = 0;
    size_t src_map[128] = {0};
    for (size_t i=0; i<str.size(); ++i) {
        auto ch = str[i];
        ++src_map[ch];
        if (src_map[ch] <= dst_map[ch]) {
            ++found;
        }
        if (found == dst_len) {
            while (begin < i && src_map[str[begin]] > dst_map[str[begin]]) {
                --src_map[str[begin]];
                ++begin;
            }
            if (i - begin + 1 < min_len) {
                min_len = i - begin + 1;
                min_begin = begin;
                end = i;
            }

            ++begin;
            --src_map[str[begin]];
            --found;
        }
    }
    return str.substr(min_begin, min_len);
}

int main() {
    std::string a = "abcabcbndea";
    std::cout << get_shorttest_cover_substring(a) << std::endl;
    return 0;
}

