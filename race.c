#include "race.h"

void set(Race* race, RaceType type, int max_hp, int attack, int defense, int shifting, int scope)
{
	race->type = type;
	race->max_hp = max_hp;
	race->attack = attack;
	race->defense = defense;
	race->shifting = shifting;
	race->scope = scope;
}

Race* create_race(RaceType type)
{
	Race* result = malloc(sizeof(Race));
	switch(type)
	{
		case TRICKSTER:
			set(result, TRICKSTER, 5, 4, 0, 4, 1);
			break;
		case SOLDIER:
			set(result, SOLDIER, 5, 2, 3, 2, 1);
			break;
		case ARCHER:
			set(result, ARCHER, 3, 3, 1, 2, 3);
			break;
		default:
			set(result, NONE_RACE, 0, 0, 0, 0, 0);
	}
	return result;
}

char get_char(RaceType type){
	switch(type)
	{
		case TRICKSTER:
			return 'F';
		case SOLDIER:
			return 'S';
		case ARCHER:
			return 'A';
		default: 
			return ' ';
	}
}

Race* copy_race(Race* race) {
	Race* copy = malloc(sizeof(Race));
	copy->attack = race->attack;
	copy->defense = race->defense;
	copy->max_hp = race->max_hp;
	copy->scope = race->scope;
	copy->shifting = race->shifting;
	copy->type = race->type;
	return copy;
}