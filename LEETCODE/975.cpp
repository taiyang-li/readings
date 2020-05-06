#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <functional>
#include <map>
#include <iterator>
using std::vector;

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        _val2idx.clear();
        int n = A.size();
        _odd_next.resize(n, -1);
        _even_next.resize(n, -1);
        for (int i=n-1; i>=0; --i) {
            if (i == n) {
                _val2idx[A[i]] = i;
                continue;
            }
            
            auto odd_it = _val2idx.lower_bound(A[i]);
            if (odd_it != _val2idx.end()) {
                _odd_next[i] = odd_it->second;
            }
            auto even_it = _val2idx.upper_bound(A[i]);
            if (even_it != _val2idx.begin()) {
                _even_next[i] = std::prev(even_it)->second;
            }
            _val2idx[A[i]] = i;
        }

        _table.resize(n, std::vector<int>(2, -1));
        _table[n-1][0] = 1;
        _table[n-1][1] = 1;
        int ret = 0;
        for (int i=0; i<n; ++i) {
            if (dfs(i, 1, n-1) == 1) {
                ret++;
            }
        }
        return ret;
    }

    int dfs(int start, int is_odd, int target) {
        if (start >= target) {
            _table[start][0] = 1;
            _table[start][1] = 1;
            return 1;
        }

        if (_table[start][is_odd] != -1) {
            return _table[start][is_odd];
        }

        if (is_odd) {
            if (_odd_next[start] == -1) {
                _table[start][is_odd] = 0;
            } else {
                _table[start][is_odd] = dfs(_odd_next[start], 1 - is_odd, target);
            }
        } else {
            if (_even_next[start] == -1) {
                _table[start][is_odd] = 0;
            } else {
                _table[start][is_odd] = dfs(_even_next[start], 1 - is_odd, target);
            }
        }
        return _table[start][is_odd];
    }

protected:
    std::map<int, int> _val2idx;
    std::vector<int> _odd_next;
    std::vector<int> _even_next;
    std::vector<std::vector<int> > _table;
};

int main() {
    // std::vector<int> A = {2,3,1,1,4};
    std::vector<int> A = {10,13,12,14,15};
    std::cout << Solution().oddEvenJumps(A) << std::endl;
    return 0;
}
