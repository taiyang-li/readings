#ifndef __LEETCODE_HEAP_H__
#define __LEETCODE_HEAP_H__

#include <cstdio>
#include <vector>
using std::vector;

enum HeapType {MAXHEAP = 0, MINHEAP};

class Heap
{
  public:
    static Heap* create_heap(vector<int>& nums);

    Heap();
    ~Heap();

    void push(int n);
    int pop();

    void show() const;
    
  private:
    void adjust_upward();
    void adjust_downward();
    size_t find_max_child(size_t idx);

  private:
    vector<int> heap_;
    size_t size_;
};


#endif  /*HEAP_H*/
