#include <stack>
#include <iostream>

struct Entry
{
  int val;
  int min;
};

class MinStack {
  public:
    MinStack() { }

    void push(int x) {
      Entry e;
      e.val = x;
      e.min = x;
      if (stack_.empty())
      {
        stack_.push(e);
        return;
      }

      Entry top_e = stack_.top();
      e.min = (x < top_e.min) ? x : top_e.min;
      stack_.push(e);
    }

    void pop() {
      stack_.pop();
    }

    int top() {
      if (stack_.empty())
        return -1;

      Entry top_e = stack_.top();
      return top_e.val;
    }

    int getMin() {
      if (stack_.empty())
        return -1;

      Entry top_e = stack_.top();
      return top_e.min;
    }

  private:
    std::stack<Entry> stack_;
};

int main()
{
  MinStack minStack;
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  std::cout << minStack.getMin() << std::endl;  
  minStack.pop();
  std::cout << minStack.top() << std::endl;    
  std::cout << minStack.getMin() << std::endl;  
  return 0;
}

