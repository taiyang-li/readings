#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "list.h"
using std::vector;

typedef ListNode* PtrListNode;
ListNode* reverseList(ListNode* head)
{
  if (! head)
    return NULL;

  int len = lenList(head);
  PtrListNode* nodes = new PtrListNode[len];
  PtrListNode curr = head;
  int idx = 0;
  while (curr)
  {
    nodes[idx] = curr;
    curr = curr->next;
    nodes[idx]->next = NULL;
    idx++;
  }

  PtrListNode ret = nodes[len-1];
  PtrListNode tail = nodes[len-1];
  for (idx=len-2; idx>=0; --idx)
  {
    tail->next = nodes[idx];
    tail = tail->next;
  }
  tail->next = NULL;

  delete [] nodes;
  return ret;
}

int main()
{
  vector<int> nums = {1, 2, 3, 6, 4, 5, 6};

  List list = creatList(nums);
  showList(list.head);

  PtrListNode head = reverseList(list.head);
  showList(head);
  return 0;
}

