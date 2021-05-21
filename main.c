#include "main.h"
#include "game.h"

int main()
{
	printf("Program starting..\n");

	Game g = init_game();
	printf("Board initialized\n");
	
	display_board(g.board);
	char res;
	printf("Start a new game ? Y/N \n");
	scanf("%c", &res);

	while (res == 'Y') {
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
		printf("Board initialized\n");
		
		display_board(g.board);

		//TODO: régler le problème avec l'utilisation de board de g (game)
		playGame(g);

		printf("Start a new game ? Y/N \n");
		scanf("%c", &res);		
	}
	printf("Stop running\n");
	return 0; // No error 
}