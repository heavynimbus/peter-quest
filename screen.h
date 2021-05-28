#include "main.h"

#define set_pos(x, y) printf("\033[%d;%dH", (y), (x))

int get_pos(int *y, int *x);