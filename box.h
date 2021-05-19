#include "main.h"
#include "hero.h"

typedef struct{
	Hero* hero;
	int x;
	char y;
}Box;

Box create_box(int x, char y, Hero* hero); 
