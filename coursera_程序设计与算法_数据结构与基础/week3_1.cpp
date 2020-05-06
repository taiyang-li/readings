#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

string encrypt(const string& input)
{
  string output(input);
  for (size_t i=0; i<input.size(); ++i)
  {
    if (input[i] >= 'A' && input[i] <= 'Z')
      output[i] = (input[i] - 'A' + 1) % 26 + 'A';
    else if (input[i] >= 'a' && input[i] <= 'z')
      output[i] = (input[i] - 'a' + 1) % 26 + 'a';
  }
  return output;
}

int main()
{
  string tmp;
  int n = 0;
  getline(cin, tmp);
  n = atoi(tmp.c_str());
  for (int i=0; i<n; i++)
  {
    string input;
    getline(cin, input);
    string output = encrypt(input);
    cout << output << endl;
  }
  return 0;
}
