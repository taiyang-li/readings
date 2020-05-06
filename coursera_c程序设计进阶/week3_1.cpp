#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXSIZE 512

enum CharState 
{
  UNKNOWN,
  BLANK,
  NONBLAN
};

void reverse_line(const string& input, string& output)
{
  if (input.empty())
  {
    output = "";
    return;
  }

  CharState prev_state = UNKNOWN;
  CharState curr_state = UNKNOWN;
  size_t i = 0;
  for (; i<input.size(); i++)
  {
    curr_state = (input[i] == ' ') ? BLANK : NONBLAN;
    if (curr_state != UNKNOWN && prev_state != UNKNOWN)
      if ( curr_state != prev_state)
        break;
    prev_state = curr_state;
  }
  // cout << "i:" << i << endl;

  // cout << "input:" << input << endl;
  reverse_line(input.substr(i), output);

  string word = input.substr(0, i);
  reverse(word.begin(), word.end());
  output += word;
  // cout << "output:" << output << endl;
}

int main()
{
  string input(MAXSIZE, '\0');
  string output(MAXSIZE, '\0');
  getline(cin, input);
  reverse_line(input, output);
  cout << output << endl;
  return 0;
}
