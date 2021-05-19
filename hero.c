#include "hero.h"

Hero create_hero(char type, char race){
	return (Hero){type, race};
}