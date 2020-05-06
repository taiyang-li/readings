#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> merge_and(std::vector<std::vector<int> >& rindexes) {
    if (rindexes.empty()) {
        return {};
    }
    const int n = rindexes.size();
    if (n == 1 || rindexes[0].empty()) {
        return rindexes[0];
    }

    int x = rindexes[0][0];
    int count = 1;
    int idx = 1;
    std::vector<int> ret;
    while (1) {
        auto it = std::lower_bound(rindexes[idx].begin(), rindexes[idx].end(), x);
        if (it == rindexes[idx].end()) {
            return ret;
        }

        if (*it == x) {
            if (++count == n) {
                ret.push_back(x);
                if (++it == rindexes[idx].end()) {
                    return ret;
                }
            }
        } else {
            count = 1;
        }
        x = *it;
        idx = (idx+1) % n;
    }
}

int main() {
    std::vector<std::vector<int> > rindexes = {{1, 3, 5}, {1, 2, 3}, {2, 3, 4, 6}};
    auto ret = merge_and(rindexes);
    for (auto x: ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
