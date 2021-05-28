#include "main.h"
#include "game.h"

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

char* ask_player_name(int id){
	show_logo();
	char* result = calloc(30, sizeof(char));
	printf("Player %d\nEntrez votre nom:\t", id);
	fgets(result, 30, stdin);
	if(result[strlen(result)-1]=='\n')result[strlen(result)-1]=0;
	return result;
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
				case 1: ;
					char* player1_username = ask_player_name(1);
					char* player2_username = ask_player_name(2);
					Game g = init_game();
					set_player(g, player1_username, HUMAN, 1);
					set_player(g, player2_username, HUMAN, 2);
					display_player(g.player1);
					display_player(g.player2);
					
					display_board(g.board);
					// faire la suite du jeu
					play_game_2p(g);
					int selection3 = menu(2,"Deplacer un pion", "Attaquer");
					switch(selection3)
					{
						case 0:
							printf("Déplacement d'un pion\n");
							return main();
						case 1: 
							return main();
					}
					return main();
				case 2: return main();
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