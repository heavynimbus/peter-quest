#include "main.h"

typedef enum {
	ALLY, ENEMY
}HeroType;

typedef struct{
	HeroType type;
	char race;
}Hero;

// create an hero
Hero create_hero(HeroType type, char race);

// display the hero for debug
void display_hero(Hero* hero);
/*

typedef enum {

}RaceType;
typedef struct {

}Race;

*/