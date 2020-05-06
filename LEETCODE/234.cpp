#include "util.h"
#include "list.h"

bool isPalindrome(ListNode* head) 
{
  if (! head)
    return true;

  int len = ::lenList(head);
  if (len == 1)
    return true;

  ListNode* mid1 = head;
  for (int i=0; i<len/2-1; ++i)
    mid1 = mid1->next;
  ListNode* mid2 = mid1->next;

  ListNode* left = head;
  ListNode* right = mid2;
  mid1->next = NULL;
  if (len % 2)
  {
    right = right->next;
    mid2->next = NULL;
  }
  showList(left);
  showList(right);
  right = reverseList(right);
  showList(right);
  while (left && right)
  {
    if (left->val != right->val)
      return false;
    left = left->next;
    right = right->next;
  }
  return true;
}

int main()
{
  vector<int> nums1 = {1,2,3,4,5,6};
  vector<int> nums2 = {1,2,3,3,2,1};
  vector<int> nums3 = {1, 0, 0};

  List list1 = creatList(nums1);
  List list2 = creatList(nums2);
  List list3 = creatList(nums3);

  std::cout << ::stringify(isPalindrome(list1.head)) << std::endl;
  std::cout << ::stringify(isPalindrome(list2.head)) << std::endl;
  std::cout << ::stringify(isPalindrome(list3.head)) << std::endl;

  return 0;
}

