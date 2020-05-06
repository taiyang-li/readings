#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef vector<vector<char> > VecVecChar;

void infect(int row, int col, VecVecChar& tmp)
{
  int len = tmp.size();
  // up 
  if (row > 0 && tmp[row-1][col] == '.')
    tmp[row-1][col] = '@';
  // down 
  if (row < len-1 && tmp[row+1][col] == '.')
    tmp[row+1][col] = '@';
  // left 
  if (col > 0 && tmp[row][col-1] == '.')
    tmp[row][col-1] = '@';
  // right
  if (col < len-1 && tmp[row][col+1] == '.')
    tmp[row][col+1] = '@';
}

void infect(VecVecChar& rooms, VecVecChar& tmp)
{
  int len = rooms.size();
  for (int i=0; i<len; ++i)
  {
    for (int j=0; j<len; ++j)
    {
      if (rooms[i][j] == '@')
        infect(i, j, tmp);
    }
  }
}

int count_infected(VecVecChar& rooms)
{
  int len=rooms.size();
  int sum = 0;
  for (int i=0; i<len; ++i)
    sum += count(rooms[i].begin(), rooms[i].end(), '@');
  return sum;
}


int main()
{
  int n;
  cin >> n;
  VecVecChar rooms;
  for (int i=0; i<n; ++i)
  {
    rooms.push_back(vector<char>());
    for (int j=0; j<n; ++j)
    {
      char ch;
      cin >> ch;
      rooms[i].push_back(ch);
    }
  }

  VecVecChar tmp = rooms;;
  int cur_day = 1;
  int end_day ;
  cin >> end_day;
  while (cur_day < end_day)
  {
    infect(rooms, tmp);
    cur_day++;
    rooms = tmp;
  }
  cout << count_infected(rooms) << endl;
  return 0;
}
