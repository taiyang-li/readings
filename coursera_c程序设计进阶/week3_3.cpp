#include <cstring>
#include <string>
#include <iostream>
#include <stack>
using namespace std;

struct Elem
{
  int id;
  char ch;
  Elem(int n, char c) : id(n), ch(c) {}
};

void show_pairs(const string& input)
{
  if (input.empty())
    return;

  stack<Elem> s;
  char first;
  for (size_t i=0; i<input.size(); ++i)
  {
    int curr_id = i;
    if (i == 0)
    {
      first = input[i];
      s.push(Elem(curr_id, input[i]));
      continue;
    }

    if (input[i] == first)
    {
      s.push(Elem(curr_id, input[i]));
    }
    else
    {
      Elem tmp = s.top();
      cout << tmp.id << " " << curr_id << endl;
      s.pop();
    }
  }
}
int main()
{
  string input;
  cin >> input;
  show_pairs(input);
  return 0;
}
