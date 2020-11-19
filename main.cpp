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
    // timing fast vs slow algorithm for making public key
  struct timeval start_fast, end_fast, start_slow, end_slow;
  int pk_x;
  int pk_y;
  
  gettimeofday(&start_slow,NULL);
  make_pk_slow(18, P_x, P_y, &pk_x, &pk_y, MODULUS, a); 
  gettimeofday(&end_slow,NULL);
  double elapsed_slow = (((end_slow.tv_sec*1000000.0 + end_slow.tv_usec) -
                        (start_slow.tv_sec*1000000.0 + start_slow.tv_usec)) / 1000000.00);
  printf("Public Key: (%u, %u), Time (slow): %f\n",pk_x,pk_y,elapsed_slow);


  gettimeofday(&start_fast,NULL);
  make_pk_fast(18, P_x, P_y, &pk_x, &pk_y, MODULUS, a); 
  gettimeofday(&end_fast,NULL);
  double elapsed_fast = (((end_fast.tv_sec*1000000.0 + end_fast.tv_usec) -
                        (start_fast.tv_sec*1000000.0 + start_fast.tv_usec)) / 1000000.00);
  printf("Public Key: (%u, %u), Time (fast): %f\n",pk_x,pk_y,elapsed_fast);
  
  /* Demonstration */
  printf("--------------------------------------\n");
  printf("              Demonstration           \n");
  printf("--------------------------------------\n");

    // entity 1
  int pk1_x;
  int pk1_y;
  make_pk_fast(3, P_x, P_y, &pk1_x, &pk1_y, MODULUS, a); 
  printf("Public Key 1: %u, %u\n", pk1_x, pk1_y);

    // entity 2
  int pk2_x;
  int pk2_y;
  make_pk_fast(10, P_x, P_y, &pk2_x, &pk2_y, MODULUS, a); 
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
