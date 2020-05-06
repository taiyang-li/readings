#include <vector>
#include <iostream>
#include "list.h"
using std::vector;

ListNode* removeElements(ListNode* head, int val)
{
  if (! head)
    return NULL;

  ListNode* prev = NULL;
  ListNode* curr = head;
  ListNode* next = NULL;
  while (curr)
  {
    next = curr->next;
    if (curr->val != val)
    {
      prev = curr;
      curr = next;
      continue;
    }

    if (prev)
      prev->next = next;
    else 
      head = next;

    delete curr;
    curr = next;
  }
  return head;
}

int main()
{
  vector<int> nums = {1, 2, 3, 6, 4, 5, 6};
  int val = 6;
  List list = creatList(nums);
  showList(list.head);
  ListNode* head = removeElements(list.head, val);
  showList(head);
  return 0;
}

