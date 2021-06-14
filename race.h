#include "main.h"

typedef enum {
	TRICKSTER, SOLDIER, ARCHER, NONE_RACE
}RaceType;

typedef struct {
	RaceType type;
	int max_hp;
	int attack;
	int defense;
	int shifting;
	int scope;
} Race;


Race* create_race(RaceType type);

char get_char(RaceType type);

Race* copy_race(Race* race);