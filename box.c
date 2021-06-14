#include "box.h"

Box create_box(int line, int column, Hero* hero)
{
	return (Box){hero, line, column};
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
	sprintf(result, "%lc%c(%c,%d): %ls %d%lc %d%lc %d%lc",(box.hero->is_tired)?SLEEP:' ', get_char(box.hero->race->type), box.line + 'a', box.column + 1, health, box.hero->race->attack, SWORD, box.hero->race->defense, SHIELD, box.hero->race->shifting, FOOT);
	return result;
}