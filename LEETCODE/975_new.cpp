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

        _odd_prev.resize(n, std::vector<int>());
        _even_prev.resize(n, std::vector<int>());
        for (int i=0; i<n; ++i) {
            if (_odd_next[i] != -1) {
                _odd_prev[_odd_next[i]].push_back(i);
            }
            if (_even_next[i] != -1) {
                _even_prev[_even_next[i]].push_back(i);
            }
        }

        _table.resize(n, std::vector<int>(2, 0));
        _table[n-1][0] = 1;
        _table[n-1][1] = 1;
        fill_table(n-1, 0);
        fill_table(n-1, 1);
        int ret = 0;
        for (int i=0; i<n; ++i) {
            std::cout << _table[i][0] << " " << _table[i][1] << std::endl;
            if (_table[i][0] == 1) {
                ret++;
            }
        }
        return ret;
    }

    void fill_table(int target, int is_odd) {
        if (_table[target][is_odd] == 0) {
            return;
        } 
        
        std::vector<int>* prevs = NULL;
        if (is_odd) {
            if (_odd_prev[target].empty()) {
                return;
            }
            prevs = &_odd_prev[target];
        } else {
            if (_even_prev[target].empty()) {
                return;
            }
            prevs = &_even_prev[target];
        }
        for (auto it = prevs->begin(); it != prevs->end(); ++it) {
            _table[*it][1 - is_odd] = 1;
            fill_table(*it, 1 - is_odd);
        }
    }


protected:
    std::map<int, int> _val2idx;
    std::vector<int> _odd_next;
    std::vector<int> _even_next;
    std::vector<std::vector<int> > _odd_prev;
    std::vector<std::vector<int> > _even_prev;
    std::vector<std::vector<int> > _table;
};

int main() {
    std::vector<int> A = {2,3,1,1,4};
    // std::vector<int> A = {10,13,12,14,15};
    std::cout << Solution().oddEvenJumps(A) << std::endl;
    return 0;
}
