#include "main.h"
#include "hero.h"

typedef struct{
	Hero* hero;
	int line;
	int column;
}Box;

// create a box
Box create_box(int line, int column, Hero* hero); 

void free_box(Box box);

char* get_hero_informations(Box box);

Box copy_box(Box box);