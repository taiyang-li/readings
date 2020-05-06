#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
using std::vector;
using std::max;

struct HPInfo
{
  int low_waterline;
  int cur_waterline;

  HPInfo(int lwl, int cwl) : low_waterline(lwl), cur_waterline(cwl) {}

  void update(const HPInfo& other)
  {
    cur_waterline += other.cur_waterline;
    if (cur_waterline < low_waterline)
      low_waterline = cur_waterline;
  }
};

void doCalculateMinimumHP(vector<vector<int> >& dungeon, int row, int col, vector<HPInfo>& candidates)
{
  HPInfo curr(dungeon[row][col], dungeon[row][col]);
  if (row == 0 && col == 0)
  {
    candidates.push_back(curr);
    return;
  }
  if (row != 0)
  {
    vector<HPInfo> up_candidates;
    doCalculateMinimumHP(dungeon, row-1, col, up_candidates);
    for (auto it=up_candidates.begin(); it!=up_candidates.end(); ++it)
      it->update(curr);
    candidates.insert(candidates.end(), up_candidates.begin(), up_candidates.end());
  }

  if (col != 0)
  {
    vector<HPInfo> left_candidates;
    doCalculateMinimumHP(dungeon, row, col-1, left_candidates);
    for (auto it=left_candidates.begin(); it!=left_candidates.end(); ++it)
      it->update(curr);
    candidates.insert(candidates.end(), left_candidates.begin(), left_candidates.end());
  }
}

// recursive method, can't pass oj because of time limit
int calculateMinimumHP1(vector<vector<int> >& dungeon)
{
  if (dungeon.empty() || dungeon[0].empty())
    return -1;

  int nrow = dungeon.size();
  int ncol = dungeon[0].size();

  vector<HPInfo> candidates;
  doCalculateMinimumHP(dungeon, nrow-1, ncol-1, candidates);
  
  int max_lwl = candidates[0].low_waterline;
  for (int i=1; i<candidates.size(); ++i)
    if (candidates[i].low_waterline > max_lwl)
      max_lwl = candidates[i].low_waterline;

  return std::max(1, 1-max_lwl);
}

// DP method, using reverse thinking
int calculateMinimumHP(vector<vector<int> >& dungeon)
{
  if (dungeon.empty() || dungeon[0].empty())
    return -1;
  
  int nrow = dungeon.size();
  int ncol = dungeon[0].size();
  vector<vector<int> > initHp(nrow, vector<int>(ncol, 0));
  for (int i=nrow-1; i>=0; i--)
  {
    for (int j=ncol-1; j>=0; j--)
    {
      if (i == nrow-1 && j == ncol-1)
      {
        initHp[i][j] = std::max(1, 1-dungeon[i][j]);
      }
      else if (i == nrow-1)
      {
        initHp[i][j] = std::max(1, initHp[i][j+1]-dungeon[i][j]);
      }
      else if (j == ncol-1)
      {
        initHp[i][j] = std::max(1, initHp[i+1][j]-dungeon[i][j]);
      }
      else
      {
        initHp[i][j] = std::max(1, std::min(initHp[i][j+1]-dungeon[i][j], initHp[i+1][j]-dungeon[i][j]));
      }
    }
  }
  return initHp[0][0];
}

int main()
{
  vector<vector<int> > dungeon = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  // vector<vector<int> > dungeon = {{1, -3, 3}, {0, -2, 0}, {-3, -3, -3}};
  std::cout << calculateMinimumHP(dungeon) << std::endl;
  return 0;
}
