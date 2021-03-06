#include "hero.h"

Hero* create_hero(HeroType type, RaceType race){
	Hero* result = malloc(sizeof(Hero));
	result->type = type;
	result->race = create_race(race);
	result->hp = result->race->max_hp;
	result->is_tired = 0;
	return result;
}

void display_hero(Hero* hero){
	if(hero != NULL){
		char* type;
		switch(hero->type){
			case BLUE:
				type = "blue";
				break;
			case RED:
				type = "red";
				break;
			case NONE_HERO:
				type = "none_hero";
		}
		switch(hero->race->type)
		{
			case TRICKSTER:
				printf("Hero(%s, %s ,%d)\n","trickster", type, hero->hp);
				break;
			case SOLDIER:
				printf("Hero(%s, %s ,%d)\n","soldier", type, hero->hp);
				break;
			case ARCHER:
				printf("Hero(%s, %s ,%d)\n","archer", type, hero->hp);
				break;
			case NONE_RACE:
				printf("Hero(%s, %s ,%d)\n","none", type, hero->hp);
				break;
		}

	} 
}



void free_hero(Hero* hero){
	free(hero->race);
	free(hero);
}

void attack(Hero* ally, Hero* enemy)
{
	int damages = ally->race->attack - enemy->race->defense;
	if(damages <= 0) damages = 1;
	enemy->hp -= damages;
}
