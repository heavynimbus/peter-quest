// system imports
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/ioctl.h>


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
#define SLEEP 0x1F4A4

#define TOP_LEFT_CORNER 0x2554
#define TOP_RIGHT_CORNER 0x2557
#define TOP_MIDDLE 0x2564

#define BOTTOM_LEFT_CORNER 0x255A
#define BOTTOM_RIGHT_CORNER 0X255D
#define BOTTOM_MIDDLE 0x2567

#define FILLING_LEFT 0x255f
#define FILLING_RIGHT 0x2562
#define FILLING_MIDDLE 0x253c

#define DOUBLE_HORIZONTAL 0x2550
#define SIMPLE_HORIZONTAL 0x2500
#define DOUBLE_VERTICAL 0x2551
#define SIMPLE_VERTICAL 0x2502

void between(int* value, int min, int max);
