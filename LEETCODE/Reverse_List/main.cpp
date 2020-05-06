#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* reverse_list_recursively(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* newhead = reverse_list_recursively(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newhead;
}

ListNode* reverse_list_unrecursively(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* prev = head;
    ListNode* curr = head->next;
    while (curr != nullptr) {
        ListNode* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    head->next = nullptr;
    return prev;
}

void print_list(ListNode* head) {
    while (head) {
        std::cout << head->val << "->" ;
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    
    ListNode* newhead = reverse_list_recursively(head);
    print_list(newhead);

    ListNode* newhead1 = reverse_list_unrecursively(newhead);
    print_list(newhead1);
    return 0;
}
