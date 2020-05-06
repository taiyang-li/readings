#include <stack>
#include <iostream>
using std::stack;

class MyQueue {
  public:
    /** Initialize your data structure here. */
    MyQueue() {
    }

    /** Push element x to the back of queue. */
    void push(int x) {
      stack1_.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
      int elem = peek();
      stack2_.pop();
      return elem;
    }

    /** Get the front element. */
    int peek() {
      if (stack2_.empty())
        transfer();
      return stack2_.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
      return stack1_.empty()  && stack2_.empty();
    }

  private:
    void transfer()
    {
      int elem = 0;
      while (! stack1_.empty())
      {
        elem = stack1_.top();
        stack1_.pop();
        stack2_.push(elem);
      }
    }

  private:
    stack<int> stack1_;
    stack<int> stack2_;
};

int main()
{
  MyQueue q;
  q.push(1);
  std::cout << q.peek() << std::endl;
  q.push(2);
  std::cout << q.peek() << std::endl;
  q.push(3);
  std::cout << q.peek() << std::endl;

  q.pop();
  std::cout << q.peek() << std::endl;
  q.pop();
  std::cout << q.peek() << std::endl;
  return 0;
}
