#include "box.h"

Box create_box(int x, char y, Hero* hero)
{
	return (Box){hero, x, y};
}

int contains_hero(Box box)
{
	return box.hero != NULL;
}

void free_box(Box box)
{
	free_hero(box.hero);
}

char* get_hero_informations(Box box) {
	char* result = calloc(30, sizeof(char));
	int nb_heart = box.hero->race->max_hp ;
	wchar_t* health = calloc( 30, sizeof(wchar_t*));
	for(int i = 0; i < nb_heart ; i++)
	{
		health[i]= (i < box.hero->hp)? FULL_HEART: EMPTY_HEART;
	}
	health[nb_heart] = 0;
	sprintf(result, "%c(%c,%d): %ls %d%lc %d%lc", get_char(box.hero->race->type), box.y, box.x, health, box.hero->race->attack, SWORD, box.hero->race->defense, SHIELD);
	return result;
}