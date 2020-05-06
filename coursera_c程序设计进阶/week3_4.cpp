#include <string>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Elem
{
  int pos;
  char ch;

  Elem(int n, char c) : pos(n), ch(c) {}

  void show() 
  {
    cout << "pos:" << pos << ",ch:" << ch << endl;
  }
};

void process(const string& input)
{
  if (input.empty())
    cout << endl;

  stack<Elem> s;
  vector<Elem> errors;
  for (size_t i=0; i<input.size(); ++i)
  {
    if (input[i] != '(' && input[i] != ')') 
      continue;

    Elem e(i, input[i]);
    if (e.ch == '(')
    {
      s.push(e);
      continue;
    }

    if (s.empty())
    {
      // e.show();
      errors.push_back(e);
      continue;
    }
    s.pop();
  }
  
  while (!s.empty())
  {
    Elem e = s.top();
    // e.show();
    errors.push_back(e);
    s.pop();
  }

  string result(input.size(), ' ');
  for (vector<Elem>::iterator it=errors.begin(); it!=errors.end(); ++it)
  {
    if (it->ch == '(')
      result[it->pos] = '$';
    else
      result[it->pos] = '?';
  }
  cout << result << endl;
}

int main()
{
  string input;
  while (cin >> input)
  {
    process(input);
  }
  return 0;
}
