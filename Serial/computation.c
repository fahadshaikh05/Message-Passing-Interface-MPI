#include<limits.h>

double computation()
{
  long i,j,k;
  double res;
  for(i=0;i<INT_MAX;i++)
  {
      double a = (double)i;
      double b = 6.4534534;
      double c = 7.86768;
      res += ((b*c) + a)/(a+1) - c - b - a;
  }
  return res;
}