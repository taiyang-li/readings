#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <map>
using std::vector;
using std::string;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode* odd_head = head;
        while (odd_head != NULL && odd_head->val % 2 == 0) {
            odd_head = odd_head->next;
        }
        if (odd_head == NULL) {
            return head;
        }

        ListNode* even_head = head;
        while (even_head != NULL && even_head->val % 2 != 0) {
            even_head = even_head->next;
        }
        if (even_head == NULL) {
            return head;
        }

        ListNode* odd_tail = odd_head;
        ListNode* even_tail = even_head;
        ListNode* curr = head;
        while (curr != NULL) {
            if (curr == odd_head || curr == even_head) {
                curr = curr->next;
                continue;
            }

            if (curr->val % 2 != 0) {
                odd_tail->next = curr;
                odd_tail = curr;
            } else {
                even_tail->next = curr;
                even_tail = curr;
            }
            curr = curr->next;
        }
        odd_tail->next = even_head;
        even_tail->next = NULL;
        return odd_head;
    }

};

int main() {
    ListNode* head =  new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* new_head = Solution().oddEvenList(head);
    while (new_head != NULL) {
        std::cout << new_head->val << std::endl;
        new_head = new_head->next;
    }
    return 0;
}
