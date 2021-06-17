#include "screen.h"

/**
    Clear the screen and print "PETER QUEST" in ascii art
*/
void show_logo()
{
    char* logo[] = {
        " _______  _______ _________ _______  _______ ",
        "| (    )|| (    \\/   ) (   | (    \\/| (    )|",
        "| (____)|| (__       | |   | (__    | (____)|",
        "|  _____)|  __)      | |   |  __)   |     __)",
        "| (      | (         | |   | (      | (\\ (",
        "| )      | (____/\\   | |   | (____/\\| ) \\ \\__",
        "|/       (_______/   )_(   (_______/|/   \\__/",
        " _______           _______  _______ _________",
        "(  ___  )|\\     /|(  ____ \\(  ____ \\__   __/",
        "| (   ) || )   ( || (    \\/| (    \\/   ) (",
        "| |   | || |   | || (__    | (_____    | |",
        "| |   | || |   | ||  __)   (_____  )   | |",
        "| | /\\| || |   | || (            ) |   | |",
        "| (_\\ \\ || (___) || (____/\\/\\____) |   | |",
        "(____\\/_)(_______)(_______/\\_______)   )_(\n"
    };

    int screen_height, screen_width;
    get_screen_dimensions(&screen_height, &screen_width);
    
    system("clear");
    for(int i = 0; i < 15; i++)
    {
        set_pos((screen_width-47)/2, i + 1);
        printf("%s", logo[i]);
    }
}


void display_messages(int argc, ...)
{
    int screen_height, screen_width;
    get_screen_dimensions(&screen_height, &screen_width);
    
    char* message;

    va_list list;    
    va_start ( list, argc );
    for (int i = 0; i < argc; i++ )
    {
        message = va_arg ( list, char* );
        
        set_pos((int)((screen_width - strlen(message))/2), 3+i);
        printf("%s\n", message);
    }
}

/**
    Display an interactive menu in the console
    agrc (int) : the count of arguments
    ... : a succession of char* arguments which can be selected

    return (int) : the index of the selected element
*/
int menu ( int argc, ... )
{
    // https://man7.org/linux/man-pages/man3/termios.3.html
    show_logo();
    static struct termios oldMask, newMask;
    va_list list;
    char **table  = NULL;
 
    int i = 0;
    int choix = -1;
    int position = 0;
 
    tcgetattr ( STDIN_FILENO, &oldMask );
    newMask = oldMask;
    newMask.c_lflag &= ~(ICANON); // avoid <enter>
    newMask.c_lflag &= ~(ECHO); // hide text typed
    tcsetattr( STDIN_FILENO, TCSANOW, &newMask );
 
    int screen_height, screen_width;
    get_screen_dimensions(&screen_height, &screen_width);
    
    table = malloc ( sizeof ( char * ) * argc );
 
    va_start ( list, argc );
    for ( i = 0; i < argc; i++ )
    {
        table[ i ] = va_arg ( list, char* );
    }
    va_end ( list );
    do
    {
        for ( i = 0; i < argc; i++ )
        {
            for(int j = 0; j < (screen_width/2)-10; j++)printf(" ");
            printf ( "%c %s\n", ( position == i )?'>':' ', table[ i ] );
        }
         
        switch ( i = getchar ( ) )
        {
            case 0x41:
            { // up key is : 0x1b5b41
                position = ( position - 1 + argc ) % argc;
                break;
            }
            case 0x42:
            { // down key is : 0x1b5b42
                position = ( position + 1 ) % argc;
                break;
            }
            case '\n':
            {
                choix = position;
                break;
            }
        }
        if ( choix < 0 )
        {
            printf ( "\e[%dA", argc );
        }
    }
    while ( choix < 0 );
 
    free ( table );
 
    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask );
 
    return ( choix );
}

void get_screen_dimensions(int* height, int* width)
{
    static struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    *height = w.ws_row;
    *width = w.ws_col;
}
