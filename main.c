#include "main.h"
#include "game.h"

int main()
{
	printf("Program starting..\n");

	Game g = init_game();


	Hero ally1 = create_hero(ALLY, 'A');
	Hero ally2 = create_hero(ALLY, 'B');
	Hero ally3 = create_hero(ALLY, 'C');
	Hero ally4 = create_hero(ALLY, 'D');
	set_hero(g.board, 1, 'b', &ally1);
	set_hero(g.board, 2, 'b', &ally2);
	set_hero(g.board, 1, 'd', &ally3);
	set_hero(g.board, 2, 'd', &ally4);

	Hero enemy1 = create_hero(ENEMY, 'W');
	Hero enemy2 = create_hero(ENEMY, 'X');
	Hero enemy3 = create_hero(ENEMY, 'Y');
	Hero enemy4 = create_hero(ENEMY, 'Z');
	set_hero(g.board, 6, 'b', &enemy1);
	set_hero(g.board, 7, 'b', &enemy2);
	set_hero(g.board, 6, 'd', &enemy3);
	set_hero(g.board, 7, 'd', &enemy4);	
	printf("Board initialized\n");
	
	display_board(g.board);

	printf("Stop running\n");
	return 0; // No error 
}