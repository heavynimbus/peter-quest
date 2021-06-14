#include "main.h"
#include "game.h"


/**
	Clear the screen and print "PETER QUEST" in ascii art
*/
void show_logo(){
	system("clear");
	set_pos(1,1);
	printf("%s", WHITE_COLOR);
	printf("\t\t\t\t\t _______  _______ _________ _______  _______ \n");
	printf("\t\t\t\t\t| (    )|| (    \\/   ) (   | (    \\/| (    )|\n");
	printf("\t\t\t\t\t| (____)|| (__       | |   | (__    | (____)|\n");
	printf("\t\t\t\t\t|  _____)|  __)      | |   |  __)   |     __)\n");
	printf("\t\t\t\t\t| (      | (         | |   | (      | (\\ (\n");   
	printf("\t\t\t\t\t| )      | (____/\\   | |   | (____/\\| ) \\ \\__\n");
	printf("\t\t\t\t\t|/       (_______/   )_(   (_______/|/   \\__/\n");
	printf("\t\t\t\t\t\n");
	printf("\t\t\t\t\t _______           _______  _______ _________\n");
	printf("\t\t\t\t\t(  ___  )|\\     /|(  ____ \\(  ____ \\__   __/\n");
	printf("\t\t\t\t\t| (   ) || )   ( || (    \\/| (    \\/   ) (\n");   
	printf("\t\t\t\t\t| |   | || |   | || (__    | (_____    | |\n");   
	printf("\t\t\t\t\t| |   | || |   | ||  __)   (_____  )   | |\n");   
	printf("\t\t\t\t\t| | /\\| || |   | || (            ) |   | |\n");   
	printf("\t\t\t\t\t| (_\\ \\ || (___) || (____/\\/\\____) |   | |\n");   
	printf("\t\t\t\t\t(____\\/_)(_______)(_______/\\_______)   )_(\n"); 
	printf("\n");
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
            printf ( " \t\t\t\t\t\t\t%c %s\n", ( position == i )?'>':' ', table[ i ] );
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


/**
	Ask the player's name
*/
void ask_player_name(Game* g, int id){
	show_logo();
	char* result = calloc(30, sizeof(char));
	printf("Player %d\nEntrez votre nom:\t", id);
	fgets(result, 30, stdin);
	if(result[strlen(result)-1]=='\n')result[strlen(result)-1]=0;
	if(strlen(result) == 0) sprintf(result, "player %d", id);
	set_player(*g, result, HUMAN, id);
}

void display_debug(int** tab)
{
    for(int i = 0; i < HEIGHT; i++){
        printf("[");
        for(int j = 0; j < WIDTH; j++)
            printf("%d\t", tab[i][j]);
        printf("]\n");
    }
}

int is_complete(int** array)
{
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
            if (array[i][j] == -2)
                return FALSE;
    return TRUE;
}

int main()
{
	show_logo();
	setlocale(LC_CTYPE, "");

	int selection1 = menu(3, "Jouer", "Regles du jeu", "Quitter");
	switch(selection1)
	{
		case 0:
			show_logo();
			int selection2 = menu(3, "1 joueur", "2 joueurs", "retour");
			switch(selection2)
			{
				case 0: 	
					printf("Cette fonctionnalité n'a pas encore été implémentée..\n");
					getchar();
					return main();
				case 1:
				{
					Game* g = init_game();
					ask_player_name(g, 1);
					ask_player_name(g, 2);
					Player* winner = run(g);
					printf("%s Vous avez gagné !!\n", winner->username);
    				free_game(g);
					return main();
				}
				case 2: return main();
			}
			break;
		case 1:
			test_function();
			return main();
		case 2:
			return 0;
	}
	return 0;
}