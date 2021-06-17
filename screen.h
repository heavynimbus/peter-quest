#include "main.h"

#define set_pos(x, y) printf("\033[%d;%dH", (y), (x))

void show_logo();

int menu ( int argc, ... );

void get_screen_dimensions(int* height, int* width);

void display_messages(int argc, ...);


/**
    Clear the screen and print "PETER QUEST" in ascii art
*/
void show_about();