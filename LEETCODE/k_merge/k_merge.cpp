#include "heap.h"
#include <list>
#include <iostream>
#include <cstdlib>

struct Node {
    std::list<int>::iterator iter;
    std::list<int>* ptr_list;

    Node(std::list<int>::iterator it, std::list<int>* p_li) : iter(it), ptr_list(p_li) {}

    bool operator<(const Node& other) {
        return (*iter) < (*other.iter);
    }

    bool operator>(const Node& other) {
        return (*iter) > (*other.iter);
    }
};

int main() {
    int k = 10;
    std::vector<std::list<int> > lists(k);
    for (auto& list: lists) {
        for (int i=0; i<50; ++i) {
            list.push_back(rand() % 1000);
        }
        list.sort();
    }

    Heap<Node> heap(MIN_HEAP);
    for (auto& list: lists) {
        heap.push(Node(list.begin(), &list));
    }
    std::list<int> ret;
    while (! heap.empty()) {
        auto node = heap.top();
        ret.push_back(*(node.iter));
        heap.pop();

        ++node.iter;
        if (node.iter != node.ptr_list->end()) {
            heap.push(node);
        }
    }

    for (auto x: ret) {
        std::cout << x << std::endl;
    }
}

