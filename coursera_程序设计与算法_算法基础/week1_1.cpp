#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;

void init_array(int n, vector<vector<int> >& arr)
{
  arr.resize(n+1);
  for (vector<vector<int> >::iterator it=arr.begin(); it!=arr.end(); ++it)
    it->resize(n+2);
  for (int i=0; i<n+1; i++)
    for (int j=0; j<n+2; j++)
      arr[i][j] = 0;
}

void clear_paint(vector<vector<int> >& paints)
{
  int n = paints.size() - 1;
  for (int i=2; i<=n; ++i)
    for (int j=1; j<=n; ++j)
      paints[i][j] = 0;
}

/*
int multiply_vector(vector<int>& left, vector<int>& right)
{
  int len = left.size();
  int sum = 0;
  for (int i=0; i<len; ++i)
  {
    sum += left[i] * right[i];
  }
  return sum;
}
*/

int paint_all_yellow(vector<vector<int> >& bricks, vector<vector<int> >& paints)
{
  int n = bricks.size() - 1;
  for (int row=2; row<=n; ++row)
  {
    for (int col=1; col<=n; ++col)
    {
      if ((bricks[row-1][col] + paints[row-1][col] + 
          paints[row-1][col-1] + paints[row-1][col+1] + paints[row-2][col]) % 2 == 0)
        paints[row][col] = 1;
    }
  }

  for (int col=1; col<=n; ++col)
  {
    if ((bricks[n][col] + paints[n][col] + paints[n][col-1] + 
        paints[n][col+1] + paints[n-1][col]) % 2 == 0)
      return -1;
  }

  int steps = 0;
  for (int i=1; i<=n; i++)
    for (int j=1; j<=n; j++)
      if (paints[i][j])
        steps++;
  // cout << "1: " << steps << endl;
  return steps;
}

bool next(vector<int>& vec)
{
  int n = vec.size() - 2;
  int i;
  for (i=n; i>=1; --i)
  {
    if (vec[i] == 0)
    {
      vec[i] = 1;
      for (int j=i+1; j<=n; ++j)
        vec[j] = 0;
      break;
    }
  }
  if (i == 0)
    return false;
  return true;
}

void execute_loop()
{
  int n;
  cin >> n;
  vector<vector<int> > bricks;
  vector<vector<int> > paints;
  init_array(n, bricks);
  init_array(n, paints);
  for (int i=1; i<=n; i++)
  {
    for (int j=1; j<=n; j++)
    {
      char ch;
      cin >> ch;
      if (ch == 'y')
        bricks[i][j] = 1;
      else if (ch == 'w')
        bricks[i][j] = 0;
    }
  }

  int min_steps = INT_MAX;
  bool has_solution = false;
  int steps = 0;
  do {
    steps = paint_all_yellow(bricks, paints);
    // cout << "2: " << steps << endl;
    if (steps >=0 && steps < min_steps)
    {
      has_solution = true;
      min_steps = steps;
    }
    clear_paint(paints);
  } while (next(paints[1]));

  if (has_solution)
    cout << min_steps << endl;
  else
    cout << "inf" << endl;
}


int main()
{
  /*
  int cases = 0;
  cin >> cases;
  */
  int cases = 1;
  for (int i=0; i<cases; ++i)
    execute_loop();
  return 0;
}
