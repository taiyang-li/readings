#ifndef __LEETCODE_LIST_H__
#define __LEETCODE_LIST_H__

#include <vector>
#include <iostream>
#include <cstdlib>
using std::vector;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct List
{
  ListNode* head;
  ListNode* tail;
};

List creatList(vector<int>& nums)
{
  List l;
  l.head = NULL;
  l.tail = NULL;
  if (nums.empty())
    return l;
  
  for (auto it=nums.begin(); it!=nums.end(); ++it)
  {
    ListNode* tmp = new ListNode(*it);
    if (it == nums.begin())
    {
      l.head = tmp;
      l.tail = tmp;
      continue;
    }
    l.tail->next = tmp;
    l.tail = tmp;
  }
  return l;
}

void showList(ListNode* head)
{
  if (! head)
    return;

  ListNode* tmp = head;
  while (tmp)
  {
    std::cout << tmp->val;
    if (tmp->next)
      std::cout << "->";
    tmp = tmp->next;
  }
  std::cout << std::endl;
}

int lenList(ListNode* head)
{
  if (! head)
    return 0;

  ListNode* curr = head;
  int len = 0;
  while (curr)
  {
    len++;
    curr = curr->next;
  }
  return len;
}

ListNode* tailList(ListNode* head)
{
  if (! head )
    return NULL;

  ListNode* curr = head;
  while (curr->next)
    curr = curr->next;
  return curr;
}

ListNode* reverseList(ListNode* head)
{
  if (! head)
    return NULL;
  ListNode* tail = tailList(head);
  ListNode* curr = head;
  ListNode* next = NULL;
  while (curr != tail)
  {
    next = curr->next;

    curr->next = tail->next;
    tail->next = curr;

    curr = next;
  }
  return curr;
}




#endif
