#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include "ecdh.h"

#define P_x 5
#define P_y 1
#define MODULUS 17
#define a 2

int main(int argc, char **argv)
{
  // Test code
  int x3;
  int y3;

  point_addition(17, 6, 14, 5, 16, &x3, &y3);
  printf("Output: %u, %u\n", x3, y3);
  
  point_doubling(17, 2, 0, 6, &x3, &y3);
  printf("Output: %u, %u\n", x3, y3);

  point_doubling(17, 2, 9, 1, &x3, &y3);
  printf("Output: %u, %u\n", x3, y3);
  
    // entity 1
  int pk1_x;
  int pk1_y;
  make_pk(3, P_x, P_y, &pk1_x, &pk1_y, MODULUS, a); 
  printf("Public Key 1: %u, %u\n", pk1_x, pk1_y);

    // entity 2
  int pk2_x;
  int pk2_y;
  make_pk(10, P_x, P_y, &pk2_x, &pk2_y, MODULUS, a); 
  printf("Public Key 2: %u, %u\n", pk2_x, pk2_y);

    // shared secret key for entity 1
  int shared1_x;
  int shared1_y;
  get_shared_key(3, pk2_x, pk2_y, &shared1_x, &shared1_y, MODULUS, a);
  printf("Shared Key (entity 1): %u, %u\n", shared1_x, shared1_y);
 
    // shared secret key for entity 2
  int shared2_x;
  int shared2_y;
  get_shared_key(10, pk1_x, pk1_y, &shared2_x, &shared2_y, MODULUS, a);
  printf("Shared Key (entity 2): %u, %u\n", shared1_x, shared1_y);
}
