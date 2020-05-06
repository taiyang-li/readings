#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <stack>
#include <cstdint>
#include <set>
#include <map>
#include <functional>
using namespace std;

enum Type {
    START = 0,
    END,
    BOTH
};

struct Status {
    Type type;
    int book;
    Status(Type t) : type(t), book(0) {}
};

/*
class PointCmp {
    public:
        bool operator()(const Point& left, const Point& right) {
            return std::less<int>()(left.value, right.value);
        }
};
*/

class MyCalendarThree {
public:
    MyCalendarThree() {
        _max_book = 0;
    }

    /*
    int book(int start, int end) {
        Point sp = {start, true};
        Point ep = {end, false};
        auto sit = _intervals.lower_bound(sp);
        auto eit = _intervals.upper_bound(ep);
        // no intersection intervals
        if (sit == eit) {
            _intervals.insert(sp);
            _intervals.insert(ep);
            return _intervals.size() / 2;
        }
        bool should_insert_start = sit != _intervals.end() ? sit->is_start : true;
        bool should_insert_end = eit != _intervals.end() ? eit->is_start : true;;
        _intervals.erase(sit, eit);
        if (should_insert_start) {
            _intervals.insert(sp);
        }
        if (should_insert_end) {
            _intervals.insert(ep);
        }
        return _intervals.size() / 2;
    }
    */

    typedef std::map<int, Status>::iterator IntervalIterator;
    typedef std::pair<IntervalIterator, IntervalIterator> IteratorPair;
    int book(int start, int end) {
        std::pair<int, Status> sp(start, Status(START));
        std::pair<int, Status> ep(end, Status(END));
        IteratorPair start_range = _intervals.equal_range(sp.first);
        IteratorPair end_range = _intervals.equal_range(ep.first);
        IntervalIterator start_it = start_range.first;
        IntervalIterator end_it = end_range.first;

        if (start_range.first == start_range.second) {
            start_it = _intervals.insert(sp).first;
            if (start_it != _intervals.begin()) {
                IntervalIterator tmp = start_it;
                --tmp;
                if (tmp->second.type != END) {
                    start_it->second.book = tmp->second.book;
                    start_it->second.type = BOTH;
                }
            }
        } else {
            if (start_it->second.type != START) {
                start_it->second.type = BOTH;
            }
        }

        if (end_range.first == end_range.second) {
            end_it = _intervals.insert(ep).first;
            if (end_range.first != _intervals.end()) {
                if (end_range.first->second.type != START) {
                    IntervalIterator tmp = end_it;
                    --tmp;
                    end_it->second.book = tmp->second.book;
                    end_it->second.type = BOTH;
                }
            }
        } else {
            if (end_it->second.type == START) {
                end_it->second.type = BOTH;
            }
        }

        for (IntervalIterator sit = start_it; sit != end_it; ++sit) {
            if (start_it != sit) {
                sit->second.type = BOTH;
            }
            _max_book = std::max(_max_book, ++sit->second.book);
        }
        return _max_book;
    }
private:
    std::map<int, Status> _intervals;
    int _max_book;
};

int main() {
    MyCalendarThree obj;
    /*
    std::cout << obj.book(10, 20) << std::endl; // returns 1
    std::cout << obj.book(50, 60) << std::endl; // returns 1
    std::cout << obj.book(10, 40) << std::endl; // returns 2
    std::cout << obj.book(5,  15) << std::endl; // returns 3
    std::cout << obj.book(5,  10) << std::endl; // returns 3
    std::cout << obj.book(25, 55) << std::endl; // returns 3
    */
    int a[][2] = {{47,50},{1,10},{27,36},{40,47},{20,27},{15,23},{10,18},{27,36},{17,25},{8,17},{24,33},{23,28},{21,27},{47,50},{14,21},{26,32},{16,21},{2,7},{24,33},{6,13},{44,50},{33,39},{30,36},{6,15},{21,27},{49,50},{38,45},{4,12},{46,50},{13,21}};
    for (int i=0; i<sizeof(a)/sizeof(int)/2; ++i) {
        std::cout << "start:" << a[i][0] << ",end:" << a[i][1] << ",result:" << obj.book(a[i][0], a[i][1]) << std::endl;
    }
    return 0;
}
