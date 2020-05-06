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

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v): val(v), next(nullptr) {}
};

class MyLinkedList {
public:
    /** Initialize your data structure here. */
    MyLinkedList() : _head(new ListNode(1)){ }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (index < 0) return -1;
        ListNode* curr = _head;
        int i = 0;
        for (; i<=index && curr != nullptr; ++i) {
            curr = curr->next;
        }
        return curr == nullptr ? -1 : curr->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ListNode* node = new ListNode(val);
        node->next = _head->next;
        _head->next = node;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        ListNode* curr = _head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        ListNode* node = new ListNode(val);
        curr->next = node;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        int i = 0;
        ListNode* curr = _head;
        for (; index >= 0 && i<index && curr != nullptr; ++i) {
            curr = curr->next;
        }
        if (curr == nullptr) return;
        ListNode* node = new ListNode(val);
        node->next = curr->next;
        curr->next = node;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index < 0) return;
        int i = 0;
        ListNode* curr = _head;
        for (; i<index && curr != nullptr; ++i) {
            curr = curr->next;
        }
        if (curr == nullptr || curr->next == nullptr) return;
        ListNode* todel = curr->next;
        curr->next = todel->next;
        delete todel;
    }

private:
    ListNode* _head;
};

int main() {
    return 0;
}

