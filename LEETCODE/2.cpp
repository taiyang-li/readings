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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int flag = 0; // 表示进位标志
    	int t;
    	ListNode *h = new ListNode(-1);   // 新生成链表的头
    	ListNode *p = h;
    	ListNode *q;

    	while(l1 != NULL || l2 != NULL)
    	{
    		if(l1 == NULL)
    		{
    			t = flag + l2->val;
    			l2 = l2->next;
    		}
    		else if(l2 == NULL)
    		{
    			t = flag + l1->val;
    			l1 = l1->next;
    		}
    		else
    		{
    			t = flag + l1->val + l2->val;
    			l1 = l1->next;
    			l2 = l2->next;
    		}

    		flag = t/10;

    		q = new ListNode(t%10);
    		p->next = q;
    		p = q;

    	}

    	if(flag)
    	{
    		q = new ListNode(flag);
    		p->next = q;
    		p = q;
    	}
    	ListNode *head = h->next;
    	free(h);
    	return head;
    }
};

int main() {
    return 0;
}

