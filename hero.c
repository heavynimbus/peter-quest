#include "hero.h"

Hero create_hero(HeroType type, char race){
	return (Hero){type, race};
}

void display_hero(Hero* hero){
	if(hero != NULL) printf("HERO(%s, %c)\n",(hero->type == ALLY)?"ally":"anemy", hero->race);
}