#include "main.h"

typedef enum{
		HUMAN, IA 
}JoueurType;

typedef struct{
	JoueurType type;
	char* username;
}Joueur;

Joueur* create_joueur(JoueurType type, char* username);