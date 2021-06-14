// system imports
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>


#define TRUE 1
#define FALSE 0

#define RED_COLOR "\033[0;31m"
#define BLUE_COLOR "\033[0;34m"
#define WHITE_COLOR "\033[0;37m"

#define RED_BACKGROUND "\33[0;41m"
#define BLUE_BACKGROUND "\33[0;44m"

#define REVERSE_BACKGROUND "\033[0;7m"
#define BLACK_BACKGROUND "\033[0;40m"

#define UNDERLINE "\033[0;4m"

#define EMPTY_HEART  0x2661
#define FULL_HEART 0x2665
#define SWORD 0x2694
#define SHIELD 0x1f6e1
#define FOOT 0x1f6b6

#define WIDTH 7
#define HEIGHT 5

/**
	Display an interactive menu in the console
	agrc (int) : the count of arguments
	... : a succession of char* arguments which can be selected

	return (int) : the index of the selected element
*/
int menu(int argc, ...);


// Clear the screen and print "PETER QUEST" in ASCII art
void show_logo();

void display_debug(int** tab);