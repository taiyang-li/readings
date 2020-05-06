#include <iostream>
#include <algorithm>
#include <utility>

struct ListNode {
    int val;
    ListNode* next;
    
    ListNode(int v): val(v), next(nullptr)  {}
};

void sort_list(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    ListNode* curr = head;
    ListNode* tail = nullptr;
    while (tail != head) {
        curr = head;
        while (curr->next != tail) {
            if (curr->val > curr->next->val) {
                std::swap(curr->val, curr->next->val);
            }
            curr = curr->next;
        }
        tail = curr;
    }
}

int main() {
    ListNode* head = new ListNode(3);
    head->next = new ListNode(5);
    head->next->next = new ListNode(4);
    sort_list(head);
    ListNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->val << std::endl;
        curr = curr->next;
    }
    return 0;
}

