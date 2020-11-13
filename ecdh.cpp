#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include "ecdh.h"

int find_inverse(int a, unsigned int m) 
{ 
  int t, s; 
  int gcd = ext_euclidian_alg(a, m, &t, &s);

  if (gcd == 1) 
  { 
    // m is added to handle negative x 
    return make_positive(t, m); 
  }
  else {
    // fprintf("Cannot find inverse\n");
    // return 1;
  }
} 

int ext_euclidian_alg(int a, int b, int *t, int *s) 
{ 
  // Base Case 
  if (a == 0)  
  { 
    *t = 0, *s = 1; 
    return b; 
  } 

  int temp_t;
  int temp_s; 
  int gcd = ext_euclidian_alg(b % a, a, &temp_t, &temp_s); 

  *t = temp_s - (b / a) * temp_t; 
  *s = temp_t; 

  return gcd; 
} 

unsigned int make_positive(int a, unsigned int m) {
  while(a < 0) {
    a += m;
  }
  return a % m;
}

void point_addition(unsigned int m, int x1, int y1, 
                    int x2, int y2, 
                    int *x3, int *y3) 
{
  int temp = make_positive(x2 - x1, m);
  int slope = make_positive((y2 - y1) * find_inverse(temp, m), m);
  *x3 = make_positive((pow(slope, 2) - x1 - x2), m);
  *y3 = make_positive((slope * (x1 - *x3) - y1), m);
}

void point_doubling(unsigned int m, int a, int x1, int y1, int *x3, int *y3) 
{
  int slope = (3 * pow(x1, 2) + a) * find_inverse(2 * y1, m);
  *x3 = make_positive(pow(slope, 2) - 2 * x1, m);
  *y3 = make_positive(slope * (x1 - *x3) - y1, m);
}