#include "main.h"
#include "board.h"

int main()
{
	printf("Program starting\n");

	Box** board = init_board();
	printf("Board initialized\n");
	display_board(board);

	printf("Stop running\n");
	return 0; // No error 
}