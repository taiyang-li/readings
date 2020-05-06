#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

class Solution {
  public:
    string multiply(string num1, string num2) {
      if (num1.empty() || num2.empty()) 
        return "";
      if (num1 == "0"  || num2 == "0")
        return "0";

      reverse(num1.begin(), num1.end());
      reverse(num2.begin(), num2.end());

      int len = num2.size(); 
      string res; 
      for (int i=0; i<len; i++)
      {

        string t = multiply_ds(num2[i], num1);

        string tt;
        for (int j=0; j<i; j++)
          tt.push_back('0');
        int len1 = t.size();
        for (int j=0; j<len1; j++)
        {
          tt.push_back(t[j]);
        }

        res = add_ss(res, tt);


      }

      reverse(res.begin(), res.end());
      return res;
    }



    pair<char, char> multiply_dd(char num1, char num2, char c_in)
    {
      int a = num1 - '0'; 
      int b = num2 - '0';
      int c = c_in- '0';
      char s_res = (a*b+c)%10 + '0';   
      char c_res = (a*b+c)/10 + '0';   
      pair<char, char> res(s_res, c_res);
      return res;
    }


    pair<char, char> add_dd(char num1, char num2, char c_in)
    {
      int a = num1-'0';
      int b = num2-'0';
      int c = c_in - '0';
      char s_res = (a+b+c)%10 + '0';  
      char c_res = (a+b+c)/10 + '0';  
      pair<char, char> res(s_res, c_res);   
      return res;
    }



    string  add_ss(string num1, string num2)
    {
      string res;
      int len1 = num1.size();
      int len2 = num2.size();
      int len = max(len1, len2); 
      pair<char, char> t('0', '0');
      for (int i=0; i<len; i++)
      {
        char c1 = (i<len1)? num1[i] : '0';   
        char c2 = (i<len2)? num2[i] : '0';
        t = add_dd(c1, c2, t.second);
        res.push_back(t.first);
      }
      if (t.second != '0')
        res.push_back(t.second);
      return res;
    }

    string multiply_ds(char num1, string num2)  {
      int len = num2.size();
      string  res;   
      pair<char, char> t('0','0');
      for(int i=0; i<len; i++)
      {
        t = multiply_dd(num1, num2[i], t.second);        
        res.push_back(t.first);                         
      }
      if (t.second != '0')
        res.push_back(t.second);
      return  res;
    }
};

int main()
{
  string num1, num2;
  cin >> num1 >> num2;
  Solution s;
  cout << s.multiply(num1, num2) << endl;
  return 0;
}
