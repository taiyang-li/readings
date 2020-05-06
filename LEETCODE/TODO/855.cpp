#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <cassert>
using namespace std;

struct Item {
    int seat;
    int distance;
    
    Item(int s=0, int d=0) : seat(s), distance(d) {}
    friend bool operator<(const Item& left, const Item& right) {
        return left.distance > right.distance || (left.distance == right.distance && left.seat < left.seat);
    }
};
class ExamRoom {
public:
    ExamRoom(int N) : _total(N), _used(0) {}
    
    int seat() {
        if (_used >= _total) {
            return -1;
        }

        if (_used <= 1) {
            int seat = _used == 0 ? 0 : _total-1;
            int distance = _used == 0 ? 0 : _total-1;
            Item item(seat, distance);
            auto ret = _items.insert(item);
            _indexes.insert(std::make_pair(seat, ret.first));
            return seat;
        }
        auto it = _items.begin();
        int seat = it->seat - (1 + it->distance)/2;
        int distance = it->distance / 2;
        Item insert_item(seat, distance);
        Item update_item(it->seat, (1+it->distance)/2);

        // update old item
        _items.erase(it);
        auto ret = _items.insert(update_item);
        _indexes[update_item.seat] = ret.first;

        // insert new item
        ret = _items.insert(insert_item);
        _indexes[insert_item.seat] = ret.first;

        ++_used;
        return seat;
    }
    
    void leave(int p) {
        auto mit = _indexes.find(p);
        if (mit == _indexes.end()) {
            return;
        }

        auto next_mit = mit;
        ++next_mit;
        int distance = mit->second->distance;
        _items.erase(mit->second);
        _indexes.erase(mit);

        // update next item
        if (next_mit != _indexes.end()) {
            Item update_item(next_mit->first, next_mit->second->distance + distance);
            _items.erase(next_mit->second);
            auto ret = _items.insert(update_item);
            next_mit->second = ret.first;
        }
        --_used;
    }

protected:
    const int _total;
    int _used;
    std::set<Item> _items;
    std::map<int, std::set<Item>::iterator> _indexes; 
};

int main() {
    ExamRoom room(10);
    std::cout << room.seat() << std::endl;
    std::cout << room.seat() << std::endl;
    std::cout << room.seat() << std::endl;
    std::cout << room.seat() << std::endl;
    room.leave(4);
    std::cout << room.seat() << std::endl;
    return 0;
}
