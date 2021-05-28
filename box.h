#include "main.h"
#include "hero.h"

typedef struct{
	Hero* hero;
	int x;
	char y;
}Box;

// create a box
Box create_box(int x, char y, Hero* hero); 

void free_box(Box box);

char* get_hero_informations(Box box);
