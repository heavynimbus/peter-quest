#include "main.h"

#define set_pos(x, y) printf("\033[%d;%dH", (y), (x))

void show_logo();

void show_about();

void show_rules();

int menu ( int argc, ... );

void get_screen_dimensions(int* height, int* width);

void display_messages(int argc, ...);


