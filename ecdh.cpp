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

// note: non-commutative (x1,y1) + (x2,y2) != (x2,y2) + (x1,y1)
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

/*
  Input:  integer to check (n)
  Output: return index of first set bit starting from the left
*/
int first_set_bit(int n)
{
  int i;
  for(i=(sizeof(int)*8)-1; i>=0; --i)
  {
    if( ((1 << i) & n) )
      return i;
  }
  return 0;
}

/*
  Input:  secret key (sk), 
          modulus (m),
          elliptic curve coeff (a), 
          primitive (P_x, P_y)
  Output: public key (T_x, T_y)
*/
void make_pk_fast(int sk, int P_x, int P_y, int *T_x, int *T_y, unsigned int m, int a)
{
  int i = 0;
  *T_x = P_x; 
  *T_y = P_y;

  for(i=first_set_bit( sk )-1; i>=0; --i) 
  {
    point_doubling(m, a, *T_x, *T_y, T_x, T_y);

    if( (1 << i) & sk ) // if the bit at index 'i' is 1 then point addition
      point_addition(m, *T_x, *T_y, P_x, P_y, T_x, T_y);
  }
}

/*
  Input:  secret key (sk), 
          modulus (m),
          elliptic curve coeff (a), 
          primitive (P_x, P_y)
  Output: public key (T_x, T_y)
*/
void make_pk_slow(int sk, int P_x, int P_y, int *T_x, int *T_y, unsigned int m, int a)
{
  point_doubling(m, a, P_x, P_y, T_x, T_y);

  sk -= 2;
  
  while(sk > 0)
  {
    point_addition(m, *T_x, *T_y, P_x, P_y, T_x, T_y);

    --sk;
  }
}

/*
  Input:  secret key (sk), 
          other entity public key (T_x, T_y),
          elliptic curve coeff (a),
          modulus (m)
  Output: shared secret key (shared_x, shared_y)
*/
void get_shared_key(int sk, int T_x, int T_y, int *shared_x, int *shared_y, unsigned int m, int a)
{
  make_pk_fast(sk, T_x, T_y, shared_x, shared_y, m, a);
}

