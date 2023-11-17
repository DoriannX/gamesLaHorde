#include "level_manager.h"
#include "spaceship.h"

int actual_level = 0;
int leveling = 0;

void next_level(void) // passe au niveau suivant
{
	leveling = 1;
	actual_level ++;
	reset_spaceship();
	reset_leveling();
}

int get_actual_level(void) // retourne le niveau actuel
{
	return actual_level;
}

int is_leveling(void) // si le niveau est en train de passer au superieur
{
	return leveling;
}

void reset_leveling(void) // reset le niveau quand la partie est recommence
{
	leveling = 0;
}