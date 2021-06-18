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

void show_about()
{
    system("clear");
	set_pos(1,1);
	printf("%s", WHITE_COLOR);

    printf("Cette application a pour but premier de s'amuser entre amis.\n");
    printf("Ne jamais oublier cela !\n");
    printf("Nous vous laissons jouer et vous éclater dessus.\n");
    printf("Créateurs : \n");
    printf("         _________ _______  ______   _______  _______                                                _______  _______  \n");
    printf("|\\     /|\\__   __/(  ____ \\(  __  \\ (  ____ \\(  ____ )                            |\\     /||\\     /|(  ____ \\(  ___  ) \n");
    printf("| )   ( |   ) (   | (    \\/| (  \\  )| (    \\/| (    )|                            | )   ( || )   ( || (    \\/| (   ) | \n");
    printf("| | _ | |   | |   | (__    | |   ) || (__    | (____)|                            | (___) || |   | || |      | |   | | \n");
	printf("| |( )| |   | |   |  __)   | |   | ||  __)   |     __)                            |  ___  || |   | || | ____ | |   | | \n");
    printf("| || || |   | |   | (      | |   ) || (      | (\\ (                               | (   ) || |   | || | \\_  )| |   | | \n");   
    printf("| () () |___) (___| (____/\\| (__/  )| (____/\\| ) \\ \\__                            | )   ( || (___) || (___) || (___) | \n");  
    printf("(_______)\\_______/(_______/(______/ (_______/|/   \\__/                            |/     \\|(_______)(_______)(_______)\n");   
    printf(" _        _______  _______  _______  _______ _________ _        _        _______            _        _______  _______\n"); 
    printf("( \\      (  ___  )(       )(  ___  )(  ____ )\\__   __/( \\      ( \\      (  ____ \\          ( \\      (  ____ \\(  ___  )\n");   
    printf("| (      | (   ) || () () || (   ) || (    )|   ) (   | (      | (      | (    \\/          | (      | (    \\/| (   ) |\n");
    printf("| |      | (___) || || || || |   | || (____)|   | |   | |      | |      | (__              | |      | (__    | |   | |\n");   
    printf("| |      |  ___  || |(_)| || |   | ||     __)   | |   | |      | |      |  __)             | |      |  __)   | |   | |\n");  
    printf("| |      | (   ) || |   | || |   | || (\\ (      | |   | |      | |      | (                | |      | (      | |   | |\n");
	printf("| (____/\\| )   ( || )   ( || (___) || ) \\ \\_____) (___| (____/\\| (____/\\| (____/\\          | (____/\\| (____/\\| (___) |\n");
    printf("(_______/|/     \\||/     \\|(_______)|/   \\__/\\_______/(_______/(_______/(_______/          (_______/(_______/(_______)\n");
    printf(" _______ _________ _______          _________ _______  _         _________          _______  _______  _______  _______ \n");
    printf("(  ____ \\__   __/(  ____ \\|\\     /|\\__   __/(  ____ \\( (    /|  \\__   __/|\\     /|(  ___  )(       )(  ___  )(  ____ \\ \n");
    printf("| (    \\/   ) (   | (    \\/| )   ( |   ) (   | (    \\/|  \\  ( |     ) (   | )   ( || (   ) || () () || (   ) || (    \\/\n");
    printf("| (__       | |   | |      | (___) |   | |   | (__    |   \\ | |     | |   | (___) || |   | || || || || (___) || (_____ \n");
    printf("|  __)      | |   | |      |  ___  |   | |   |  __)   | (\\ \\) |     | |   |  ___  || |   | || |(_)| ||  ___  |(_____  )\n");
    printf("| (         | |   | |      | (   ) |   | |   | (      | | \\   |     | |   | (   ) || |   | || |   | || (   ) |      ) |\n");
    printf("| )      ___) (___| (____/\\| )   ( |   | |   | (____/\\| )  \\  |     | |   | )   ( || (___) || )   ( || )   ( |/\\____) |\n");
    printf("|/       \\_______/(_______/|/     \\|   )_(   (_______/|/    )_)     )_(   |/     \\|(_______)|/     \\||/     \\|\\_______)\n");

    // char* about[] = {
    //      "Cette application a pour but premier de s'amuser entre amis.\n",
    //      ,
    //      ,
    //      ,
    //      "         _________ _______  ______   _______  _______                                                _______  _______  ",
    //      "|\\     /|\\__   __/(  ____ \\(  __  \\ (  ____ \\(  ____ )                            |\\     /||\\     /|(  ____ \\(  ___  ) ",
    //      "| )   ( |   ) (   | (    \\/| (  \\  )| (    \\/| (    )|                            | )   ( || )   ( || (    \\/| (   ) | ",
    //      "| | _ | |   | |   | (__    | |   ) || (__    | (____)|                            | (___) || |   | || |      | |   | | ",
	//      "| |( )| |   | |   |  __)   | |   | ||  __)   |     __)                            |  ___  || |   | || | ____ | |   | | ",
    //      "| || || |   | |   | (      | |   ) || (      | (\\ (                               | (   ) || |   | || | \\_  )| |   | | ",   
    //      "| () () |___) (___| (____/\\| (__/  )| (____/\\| ) \\ \\__                            | )   ( || (___) || (___) || (___) | ",  
    //      "(_______)\\_______/(_______/(______/ (_______/|/   \\__/                            |/     \\|(_______)(_______)(_______)\n",   
    //      " _        _______  _______  _______  _______ _________ _        _        _______            _        _______  _______", 
    //      "( \\      (  ___  )(       )(  ___  )(  ____ )\\__   __/( \\      ( \\      (  ____ \\          ( \\      (  ____ \\(  ___  )",   
    //      "| (      | (   ) || () () || (   ) || (    )|   ) (   | (      | (      | (    \\/          | (      | (    \\/| (   ) |",
    //      "| |      | (___) || || || || |   | || (____)|   | |   | |      | |      | (__              | |      | (__    | |   | |",   
    //      "| |      |  ___  || |(_)| || |   | ||     __)   | |   | |      | |      |  __)             | |      |  __)   | |   | |",  
    //      "| |      | (   ) || |   | || |   | || (\\ (      | |   | |      | |      | (                | |      | (      | |   | |",
	//      "| (____/\\| )   ( || )   ( || (___) || ) \\ \\_____) (___| (____/\\| (____/\\| (____/\\          | (____/\\| (____/\\| (___) |",
    //      "(_______/|/     \\||/     \\|(_______)|/   \\__/\\_______/(_______/(_______/(_______/          (_______/(_______/(_______)\n",
    //      " _______ _________ _______          _________ _______  _         _________          _______  _______  _______  _______ ",
    //      "(  ____ \\__   __/(  ____ \\|\\     /|\\__   __/(  ____ \\( (    /|  \\__   __/|\\     /|(  ___  )(       )(  ___  )(  ____ \\ ",
    //      "| (    \\/   ) (   | (    \\/| )   ( |   ) (   | (    \\/|  \\  ( |     ) (   | )   ( || (   ) || () () || (   ) || (    \\/",
    //      "| (__       | |   | |      | (___) |   | |   | (__    |   \\ | |     | |   | (___) || |   | || || || || (___) || (_____ ",
    //      "|  __)      | |   | |      |  ___  |   | |   |  __)   | (\\ \\) |     | |   |  ___  || |   | || |(_)| ||  ___  |(_____  )",
    //      "| (         | |   | |      | (   ) |   | |   | (      | | \\   |     | |   | (   ) || |   | || |   | || (   ) |      ) |",
    //      "| )      ___) (___| (____/\\| )   ( |   | |   | (____/\\| )  \\  |     | |   | )   ( || (___) || )   ( || )   ( |/\\____) |",
    //      "|/       \\_______/(_______/|/     \\|   )_(   (_______/|/    )_)     )_(   |/     \\|(_______)|/     \\||/     \\|\\_______)\n"
    // };

    // int screen_height, screen_width;
    // get_screen_dimensions(&screen_height, &screen_width);
    
    // system("clear");
    // for(int i = 0; i < 15; i++)
    // {
    //     printf("%s", about[i]);
    // }
}

/**
	Clear the screen and print all rules in ascii art
*/
void show_rules(){

    system("clear");
	set_pos(1,1);
	printf("%s", WHITE_COLOR);
	printf("\tL’aire de jeu sera modélisée par une grille de 7 cases par 5. Sur ce plateau, 4 unités ’héros’ sont placées d’un côté, et 4 autres ’ennemis’ de l’autre (voir situation initiale d’exemple).\n");
	printf("\tLa boucle principale de jeu se déroule comme ceci :\n");
	printf("\t— Le joueur courant sélectionne une de ses unités en indiquant des coordonnées de la grille.\n");
	printf("\t— En sélectionnant de nouvelles coordonnées, l’unité est déplacée.\n");
	printf("\t— Si l’unité est assez proche, elle peut alors attaquer un adversaire.\n");   
	printf("\t— Une fois le mouvement (et l’attaque) terminés, l’unité sélectionnée est alors fatiguée. Elle ne pourra pas être à nouveau sélectionnée tant qu’il restera au moins un autre unité nonfatiguée dans le camp du joueur.\n");
	printf("\t— La main passe alors au joueur suivant qui peut à son tour déplacer une unité.\n");
	printf("\n");
	printf("\tLorsque la dernière unité non-fatiguée d’un camp est jouée, tout le monde redevient à nouveau en forme. Cela implique qu’un camp une unité pourra la jouer successivement y compris contre un adversaire ayant encore de nombreuses unités (qui est donc forcé de les jouer une à une).\n");
	printf("\n");
	printf("\tLors d’une attaque, le pion attaquant et défenseur font une passe d’arme (l’attaquant inflige des dégâts, et le défenseur, s’il est encore en vie, contre-attaque). Les dégâts infligés sont égaux à la puissance du pion qui frappe réduits de la défense du pion qui est frappé (minimum 1). La partie s’arrête lorsqu’un camp ne possède plus aucune unité sur le plateau, le camp restant étant alors vainqueur. Si après 100 coups, aucun joueur n’est gagnant, le camp avec le plus de points de vie gagne, puis aléatoirement en cas de nouvelle égalité.\n");   
	printf("\n");

    // char* rules[] = {
    //      "\tL’aire de jeu sera modélisée par une grille de 7 cases par 5. Sur ce plateau, 4 unités ’héros’ sont placées d’un côté, et 4 autres ’ennemis’ de l’autre (voir situation initiale d’exemple).\n",
    //      "\tLa boucle principale de jeu se déroule comme ceci :\n",
    //      "\t— Le joueur courant sélectionne une de ses unités en indiquant des coordonnées de la grille.\n",
    //      "\t— En sélectionnant de nouvelles coordonnées, l’unité est déplacée.\n",
    //      "\t— Si l’unité est assez proche, elle peut alors attaquer un adversaire.\n",
    //      "\t— Une fois le mouvement (et l’attaque) terminés, l’unité sélectionnée est alors fatiguée. Elle ne pourra pas être à nouveau sélectionnée tant qu’il restera au moins un autre unité nonfatiguée dans le camp du joueur.\n",
    //      "\t— La main passe alors au joueur suivant qui peut à son tour déplacer une unité.\n",
    //      "\tLorsque la dernière unité non-fatiguée d’un camp est jouée, tout le monde redevient à nouveau en forme. Cela implique qu’un camp une unité pourra la jouer successivement y compris contre un adversaire ayant encore de nombreuses unités (qui est donc forcé de les jouer une à une).\n",
	//      "\tLors d’une attaque, le pion attaquant et défenseur font une passe d’arme (l’attaquant inflige des dégâts, et le défenseur, s’il est encore en vie, contre-attaque). Les dégâts infligés sont égaux à la puissance du pion qui frappe réduits de la défense du pion qui est frappé (minimum 1). La partie s’arrête lorsqu’un camp ne possède plus aucune unité sur le plateau, le camp restant étant alors vainqueur. Si après 100 coups, aucun joueur n’est gagnant, le camp avec le plus de points de vie gagne, puis aléatoirement en cas de nouvelle égalité.\n"
    // };

    // int screen_height, screen_width;
    // get_screen_dimensions(&screen_height, &screen_width);
    
    // system("clear");
    // for(int i = 0; i < 10; i++)
    // {
    //     printf("%s", rules[i]);
    // }
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
