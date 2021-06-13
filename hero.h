#include "main.h"
#include "race.h"

typedef enum {
	BLUE, RED, NONE_HERO
}HeroType;

typedef struct{
	HeroType type;
	Race* race;
	int hp;
	int is_tired;
}Hero;

// create an hero
Hero* create_hero(HeroType type, RaceType race);

// display the hero for debug
void display_hero(Hero* hero);

void free_hero(Hero* hero);

void attack(Hero* ally, Hero* enemy);