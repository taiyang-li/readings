#ifndef __EFFICIENT_CPP_CALC_H__
#define __EFFICIENT_CPP_CALC_H__

/*
int inlined_add(int a, int b);

int uninlined_add(int a, int b);
*/

inline int inlined_add(int a, int b)
{
  return a+b;
}

inline int uninlined_add(int a, int b)
{
  return a+b;
}
#endif  /*CALC_H*/
