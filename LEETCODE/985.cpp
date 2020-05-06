#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        const int query_len = queries.size();
        std::vector<int> ret(query_len, 0);
        int sum = std::accumulate(A.begin(), A.end(), 0, [](int sum, int a) -> int {return a%2==0 ? sum+a : sum;});
        int count = 0;
        for (const auto& query: queries) {
            int val = query[0];
            int idx = query[1];
            if (val % 2 == 0) {
                if (A[idx] % 2 == 0) {
                    sum += val;
                }
            } else {
                if (A[idx] % 2 == 0) {
                    sum -= A[idx];
                } else {
                    sum += A[idx] + val;
                }
            }
            ret[count++] = sum;
            A[idx] += val;
        }
        return ret;
    }
};

int main() {
    return 0;
}

