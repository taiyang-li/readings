#include <iostream>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <cstring>
using namespace std;

int moves[9][9] = {
// A  B  C  D  E  F  G  H  I
  {1, 1, 0, 1, 1},
  {1, 1, 1},
  {0, 1, 1, 0, 1, 1},
  {1, 0, 0, 1, 0, 0, 1},
  {0, 1, 0, 1, 1, 1, 0, 1},
  {0, 0, 1, 0, 0, 1, 0, 0, 1},
  {0, 0, 0, 1, 1, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 0, 1, 1}
};

int clocks[9] = {0};
int times[9] = {0};

int min_steps = 9*3;
int min_times[9] = {0};

#define at(clocks, ch) clocks[ch-'A']

int main()
{
  for (int i=0; i<9; ++i)
    cin >> clocks[i];
  for (; times[0] < 4; times[0]++)
  {
    for (; times[1] < 4; times[1]++)
    {
      for (; times[2] < 4; times[2]++)
      {
        for (; times[3] < 4; times[3]++)
        {
          // A 
          if ((at(clocks, 'A') + times[0] + times[1] + times[3]) % 4 != 0)
            continue;
          for (; times[4] < 4; times[4]++)
          {
            // B 
            if ((at(clocks, 'B') + times[0] + times[1] + times[2] + times[4]) % 4 != 0)
              continue;
            for (; times[5] < 4; times[5]++)
            {
              // C 
              if ((at(clocks, 'C') + times[1] + times[2] + times[5]) % 4 != 0)
                continue;
              for (; times[6] < 4; times[6]++)
              {
                // D
                if ((at(clocks, 'D') + times[0] + times[3] + times[4] + times[6]) % 4 != 0)
                  continue;
                for (; times[7] < 4; times[7]++)
                {
                  // G
                  if ((at(clocks, 'G') + times[3] + times[6] + times[7]) % 4 != 0)
                    continue;
                  for (; times[8] < 4; times[8]++)
                  {
                    // E 
                    if ((at(clocks, 'E') + times[2] + times[4] + times[6] + times[8]) % 4 != 0)
                      continue;
                    // F 
                    if ((at(clocks, 'F') + times[2] + times[4] + times[5] + times[8]) % 4 != 0)
                      continue;
                    // H
                    if ((at(clocks, 'H') + times[4] + times[6] + times[7] + times[8]) % 4 != 0)
                      continue;
                    // I 
                    if ((at(clocks, 'I') + times[5] + times[7] + times[8]) % 4 != 0)
                      continue;
                    
                    int steps = accumulate(times, times+9, 0);
                    if (steps < min_steps)
                    {
                      min_steps = steps;
                      ::memcpy((void*)min_times, (void*)times, sizeof(times));
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  bool first = true;
  for (int i=0; i<9; ++i)
  {
    if (min_times[i] == 0)
      continue;
    for (int j=0; j<min_times[i]; ++j)
    {
      if (first)
      {
        first = false;
      }
      else
      {
        cout << " ";
      }
      cout << i+1;
    }
  }
  cout << endl;
  return 0;
}
