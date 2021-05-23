#include "main.h"
#include "game.h"
#include "joueur.h"

int show_logo(){
	system("clear");
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
	return 0;
}

int menu ( int argc, ... )
{
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

int main()
{
	show_logo();
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
					show_logo();

					Game g = init_game();
					Hero* ally1 = create_hero(ALLY, ARCHER);
					Hero* ally2 = create_hero(ALLY, SOLDIER);
					Hero* ally3 = create_hero(ALLY, ARCHER);
					Hero* ally4 = create_hero(ALLY, TRICKSTER);
					set_hero(g.board, 1, 'b', ally1);
					set_hero(g.board, 2, 'b', ally2);
					set_hero(g.board, 1, 'd', ally3);
					set_hero(g.board, 2, 'd', ally4);

					Hero* enemy1 = create_hero(ENEMY, TRICKSTER);
					Hero* enemy2 = create_hero(ENEMY, ARCHER);
					Hero* enemy3 = create_hero(ENEMY, SOLDIER);
					Hero* enemy4 = create_hero(ENEMY, ARCHER);
					set_hero(g.board, 6, 'b', enemy1);
					set_hero(g.board, 7, 'b', enemy2);
					set_hero(g.board, 6, 'd', enemy3);
					set_hero(g.board, 7, 'd', enemy4);	
					
					display_board(g.board);
					
					menu(2,"Deplacer un pion", "Attaquer");
					return main();
			}
			break;
		case 1:
			printf("Regles du jeu\n");
			break;
		case 2:
			return 0;
	}
	return 0;
}