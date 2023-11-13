
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "special_attack.h"

int previous_click = 0;
int actual_click = 0;
int exploded = 0;
int explode(sfRenderWindow* window) // attaque special
{
	if (sfKeyboard_isKeyPressed(sfKeyLShift) && sfTime_asSeconds(sfClock_getElapsedTime(explode_time)) >= 60) { // pouvoir se reset toutes les 60 secondes
		exploded = 1; // divise tous les vaisseaux aux alentours
		sfClock_restart(explode_time);
	}

	return exploded;
}

void explode_reset(void) // reset le pouvoir
{
	exploded = 0;
}