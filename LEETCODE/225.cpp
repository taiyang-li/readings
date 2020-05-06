#include <queue>
#include <algorithm>
#include <iostream>
using std::queue;
using std::swap;

class MyStack {
  public:
    /** Initialize your data structure here. */
    MyStack() {
      top_queue = &queue1_;
      bottom_queue = &queue2_;
    }

    /** Push element x onto stack. */
    void push(int x) {
      top_queue->push(x);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
      int ret = top();
      top_queue->pop();
      swap(top_queue, bottom_queue);
      return ret;
    }

    /** Get the top element. */
    int top() {
      transfer();
      return top_queue->front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
      return top_queue->empty() && bottom_queue->empty();
    }
  private:
    void transfer()
    {
      while (top_queue->size() > 1)
      {
        int tmp = top_queue->front();
        top_queue->pop();
        bottom_queue->push(tmp);
      }
    }
    
  private:
    queue<int>  queue1_;
    queue<int>  queue2_;
    queue<int>* top_queue;
    queue<int>* bottom_queue;
};

int main()
{
  MyStack stack;
  stack.push(1);
  std::cout << stack.top() << std::endl;
  stack.push(2);
  std::cout << stack.top() << std::endl;
  stack.push(3);
  std::cout << stack.top() << std::endl;

  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  return 0;
}
