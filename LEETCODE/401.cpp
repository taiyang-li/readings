#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <functional>

using namespace std;


class Solution {
public:
    static void addWatchTimes(vector<string>& times, vector<int>& flags) {
        int hour = 0;
        for (size_t i=0; i<4; ++i) {
            hour = 2*hour + flags[i];
        }
        if (hour >= 12) return;

        int minute = 0;
        for (size_t i=4; i<10; ++i) {
            minute = 2*minute + flags[i];
        }
        if (minute >= 60) return;
        
        char buf[16];
        ::snprintf(buf, 16, "%d:%02d", hour, minute);
        times.push_back(buf);
    }

    vector<string> readBinaryWatch(int num) {
        vector<string> ret;
        CallBack cb = bind(&Solution::addWatchTimes, std::ref(ret), std::placeholders::_1);
        combination(num, cb);
        return ret;
    }

    typedef function<void (vector<int>&)> CallBack;
    void combination(int num, const CallBack& cb) {
        vector<int> flags(10, 0);
        for (int i=0; i<num; ++i) {
            flags[i] = 1;
        }

        bool has_next = true;
        int count = 0;
        while (has_next) {
            cb(flags);

            has_next = false;
            for (int i=0; i<10-1; ++i) {
                if (flags[i] == 1 && flags[i+1] == 0) {
                    flags[i] = 0;
                    flags[i+1] = 1;

                    count = 0;
                    for (int j=0; j<i; ++j) {
                        if (flags[j] == 1) {
                            count++;
                        }
                    }
                    if (count < i) {
                        for (int j=0; j<count; ++j) {
                            flags[j] = 1;
                        }
                        for (int j=count; j<i; ++j) {
                            flags[j] = 0;
                        }
                    }
                    has_next = true;
                    break;
                }
            }
        }
    }
};

int main() {
    Solution solution;
    vector<string> ret = solution.readBinaryWatch(1);
    for (const auto& x : ret) {
        std::cout << x << std::endl;
    }
    return 0;
}
