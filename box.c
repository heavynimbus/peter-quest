#include "box.h"

Box create_box(int x, char y, Hero* hero)
{
	return (Box){hero, x, y};
}

int contains_hero(Box box){
	return box.hero != NULL;
}