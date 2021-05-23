#include "main.h"
#include "race.h"

typedef enum {
	ALLY, ENEMY, NONE_HERO
}HeroType;

typedef struct{
	HeroType type;
	Race* race;
	int hp;
}Hero;

// create an hero
Hero* create_hero(HeroType type, RaceType race);

// display the hero for debug
void display_hero(Hero* hero);
