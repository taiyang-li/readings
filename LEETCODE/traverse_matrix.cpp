// given a m*n matrix, traverse the matrix clockwise, find the last position
#include <iostream>

void do_find_last_pos(int m, int n, int& x, int& y)
{
  if (m == 1)
  {
    x = 0;
    y = n-1;
    return;
  }

  if (m == 2)
  {
    x = 1;
    y = 0;
    return;
  }
  
  int x1 = 0;
  int y1 = 0;
  do_find_last_pos(m-2, n-2, x1, y1);
  x = x1+1;
  y = y1+1;
}

void find_last_pos(int m, int n, int& x, int& y)
{
  if (m == 0 || n == 0)
  {
    x = -1;
    y = -1;
    return;
  }

  if (m > n)
  {
    do_find_last_pos(n, m, y, x);
    return;
  }
  do_find_last_pos(m, n, x, y);
}

int main()
{
  int x, y;

  find_last_pos(3,3, x,y);
  std::cout << x << " " << y << std::endl;

  find_last_pos(2,2, x,y);
  std::cout << x << " " << y << std::endl;

  find_last_pos(3,6, x,y);
  std::cout << x << " " << y << std::endl;
}


