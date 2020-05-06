#include <iostream>
#include <vector>
#include "list.h"
using std::vector;

ListNode* step(ListNode* ptr, int n)
{
  if (! ptr || n < 0)
    return NULL;
  
  ListNode* tmp = ptr;
  while (n--)
  {
    tmp = tmp->next;
    if (! tmp)
      return NULL;
  }
  return tmp;
}

int listLen(ListNode* ptr)
{
  ListNode* tmp = ptr;
  int count = 0;
  while (tmp)
  {
    tmp = tmp->next;
    count++;
  }
  return count;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
  if (! headA || ! headB)
    return NULL;
  
  ListNode* tmpA = headA;
  ListNode* tmpB = headB;
  int lenA = listLen(headA);
  int lenB = listLen(headB);
  if (lenA > lenB)
    tmpA = step(tmpA, lenA-lenB);
  else if (lenA < lenB)
    tmpB = step(tmpB, lenB-lenA);

  while (tmpA && tmpB &&  tmpA != tmpB)
  {
    tmpA = tmpA->next;
    tmpB = tmpB->next;
  }
  if (tmpA && tmpB)
    return tmpA;
  return NULL;
}

int main()
{
  vector<int> vecA = {1,2};
  vector<int> vecB = {3,4,5};
  vector<int> vecC = {7,8,9}; 
  
  List listA = creatList(vecA);
  List listB = creatList(vecB);
  List listC = creatList(vecC);

  listA.tail->next = listC.head;
  listB.tail->next = listC.head;
  
  showList(listA.head);
  showList(listB.head);

  ListNode* ret = getIntersectionNode(listA.head, listB.head); 
  std::cout << ret->val << std::endl;
  return 0;
}


