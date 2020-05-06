#include <iostream>
#include <algorithm>
#include <utility>

struct ListNode {
    int val;
    ListNode* next;
    
    ListNode(int v): val(v), next(nullptr)  {}
};

void sort_list(ListNode* head, ListNode* tail) {
    if (head == nullptr || tail == nullptr || head == tail) {
        return;
    }

    int key = head->val;
    ListNode* left = head;
    ListNode* mid = head->next;
    ListNode* tmp = head;
    while (mid != nullptr && mid != tail->next) {
        if (mid->val <= key) {
            tmp = left;
            left = left->next;
            std::swap(left->val, mid->val);
        }
        mid = mid->next;
    }
    std::swap(head->val, left->val);
    sort_list(head, tmp);
    sort_list(left->next, tail);
}

int main() {
    ListNode* head = new ListNode(3);
    head->next = new ListNode(5);
    head->next->next = new ListNode(4);
    sort_list(head, head->next->next);
    ListNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->val << std::endl;
        curr = curr->next;
    }
    return 0;
}

