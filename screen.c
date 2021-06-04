#include "screen.h"

int get_pos(int *y, int *x)
{
    char buffer[30] = {0};
    int ret, i, pow;
    char ch;

    *y = 0; *x = 0;

    struct termios newmask, restore;

    tcgetattr(0, &newmask);
    tcgetattr(0, &restore);
    newmask.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(0, TCSANOW, &newmask);

    write(1, "\033[6n", 4);

    for( i = 0, ch = 0; ch != 'R'; i++ )
    {
        ret = read(0, &ch, 1);
        if ( !ret ) 
        {
            tcsetattr(0, TCSANOW, &restore);
            fprintf(stderr, "getpos: error reading response!\n");
            return 1;
        }
        buffer[i] = ch;
        printf("buffer[%d]: \t%c \t%d\n", i, ch, ch);
    }

    if (i < 2) {
        tcsetattr(0, TCSANOW, &restore);
        printf("i < 2\n");
        return(1);
    }

    for( i -= 2, pow = 1; buffer[i] != ';'; i--, pow *= 10)
        *x = *x + ( buffer[i] - '0' ) * pow;

    for( i-- , pow = 1; buffer[i] != '['; i--, pow *= 10)
        *y = *y + ( buffer[i] - '0' ) * pow;

    tcsetattr(0, TCSANOW, &restore);
    return 0;
}
