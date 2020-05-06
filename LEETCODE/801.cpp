#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>

using namespace std;

struct State {
    int a; 
    int b;
    int min_swap;
};

class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int len = int(A.size());
        State* swap_states = new State[len];
        State* unswap_states = new State[len];

        // init swap_states and unswap_states 
        swap_states[len-1] = {B[len-1], A[len-1], 1};
        unswap_states[len-1] = {A[len-1], B[len-1], 0};
        for (int i=len-2; i>=0; --i) {
            update_state(A[i], B[i], swap_states[i+1], unswap_states[i+1],
                    swap_states[i], unswap_states[i]);
        }
        int ret = std::min(swap_states[0].min_swap, unswap_states[0].min_swap);
        delete [] swap_states;
        delete [] unswap_states;
        return ret;
    }

    void update_state(int a, int b, const State& src_swap_state, const State& src_unswap_state,
            State& dst_swap_state, State& dst_unswap_state) {
        // calculate unswap states
        dst_unswap_state.a = a;
        dst_unswap_state.b = b;
        dst_unswap_state.min_swap = INT_MAX;
        if (src_swap_state.min_swap != INT_MAX && 
                a < src_swap_state.a && b < src_swap_state.b) {
            if (src_swap_state.min_swap < dst_unswap_state.min_swap) {
                dst_unswap_state.min_swap = src_swap_state.min_swap;
            }
        }
        if (src_unswap_state.min_swap != INT_MAX && 
                a < src_unswap_state.a && b < src_unswap_state.b) {
            if (src_unswap_state.min_swap < dst_unswap_state.min_swap) {
                dst_unswap_state.min_swap = src_unswap_state.min_swap;
            }
        }

        // calculate swap states
        dst_swap_state.a = b;
        dst_swap_state.b = a;
        dst_swap_state.min_swap = INT_MAX;
        if (src_swap_state.min_swap != INT_MAX &&
                b < src_swap_state.a && a < src_swap_state.b) {
            if (src_swap_state.min_swap < dst_swap_state.min_swap) {
                dst_swap_state.min_swap = src_swap_state.min_swap;
            }
        }
        if (src_unswap_state.min_swap != INT_MAX && 
                b < src_unswap_state.a && a < src_unswap_state.b) {
            if (src_unswap_state.min_swap < dst_swap_state.min_swap) {
                dst_swap_state.min_swap = src_unswap_state.min_swap;
            }
        }
        dst_swap_state.min_swap++;
    }
};

int main() {
    std::vector<int> A = {1,3,5,4};
    std::vector<int> B = {1,2,3,7};
    std::cout << Solution().minSwap(A, B) << std::endl;
    return 0;
}
