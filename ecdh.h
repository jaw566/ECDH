int find_inverse(int a, unsigned int m);
int ext_euclidian_alg(int a, int b, int *t, int *s);
void point_addition(unsigned int m, int x1, int y1, 
                    int x2, int y2, 
                    int *x3, int *y3);
unsigned int make_positive(int a, unsigned int m);

void point_doubling(unsigned int m, int a, int x1, int y1,  
                    int *x3, int *y3);

int first_set_bit(int n);
void make_pk_fast(int sk, int P_x, int P_y, int *T_x, int *T_y, 
                  unsigned int m, int a);
void make_pk_slow(int sk, int P_x, int P_y, int *T_x, int *T_y, 
                  unsigned int m, int a);
void get_shared_key(int sk, int T_x, int T_y, int *shared_x, 
                    int *shared_y, unsigned int m, int a);
