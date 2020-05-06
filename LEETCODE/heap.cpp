#include <algorithm>
#include "heap.h"
#include "tree.h"
using std::swap;

Heap* Heap::create_heap(vector<int>& nums)
{
  Heap* ret = new Heap();
  for (auto it=nums.begin(); it!=nums.end(); ++it)
    ret->push(*it);
  return ret;
}

Heap::Heap() : size_(0) {}

Heap::~Heap() {}

void Heap::push(int n)
{
  if (size_ == heap_.size())
    heap_.push_back(n);
  else
    heap_[size_] = n;
  size_++;
  adjust_upward();
}


int Heap::pop() 
{
  int ret = heap_[0];
  swap(heap_[0], heap_[size_-1]);
  size_--;

  adjust_downward();
  return ret;
}

void Heap::adjust_upward()
{
  size_t up_idx = size_-1;
  size_t parent_idx = (up_idx-1)/2;
  while (heap_[up_idx] > heap_[parent_idx] && up_idx != 0)
  {
    swap(heap_[up_idx], heap_[parent_idx]);
    up_idx = parent_idx;
    parent_idx = (up_idx-1)/2;
  }
}

void Heap::adjust_downward()
{
  size_t down_idx = 0;
  size_t child_idx = find_max_child(down_idx);
  while (child_idx != size_ && heap_[child_idx] > heap_[down_idx])
  {
    swap(heap_[down_idx], heap_[child_idx]);
    down_idx = child_idx;
    child_idx = find_max_child(down_idx);
  }
}

size_t Heap::find_max_child(size_t idx)
{
  int left = 2*idx+1;
  if (left >= size_)
    return size_;

  int right = 2*idx+2;
  if (right >= size_)
    return left;
  return (heap_[left] > heap_[right]) ? left : right;
}

void Heap::show() const 
{
  vector<int> nums(heap_.begin(), heap_.begin()+size_);
  TreeNode* root = generateTree(nums);
  std::cout << "-----------------------begin--------------------" << std::endl;
  showTree(root);
  std::cout << "------------------------end---------------------" << std::endl;
  deleteTree(root);
}
