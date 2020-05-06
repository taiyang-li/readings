#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next = node->next;
        for (; next->next != NULL; node = node->next, next = next->next) {
            node->val = next->val;
        }
        node->val = next->val;
        delete next;
        node->next = NULL;
    }
};

void print_list(ListNode* head) {
    for (; head != NULL; head = head->next) {
        std::cout << head->val << std::endl;
    }
}

int main() {
    ListNode* head = new ListNode(4);
    head->next = new ListNode(5);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(9);
    print_list(head);

    ListNode* node = head->next;
    Solution().deleteNode(node);
    print_list(head);
    return 0;
}

