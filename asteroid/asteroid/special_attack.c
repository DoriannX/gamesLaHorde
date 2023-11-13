#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "special_attack.h"
#include "print.h"

int previous_click = 0;
int actual_click = 0;
int exploded = 0;
int explode(sfRenderWindow* window)
{
	if(sfKeyboard_isKeyPressed(sfKeyLShift) && sfTime_asSeconds(sfClock_getElapsedTime(explode_time)) >= 60){
		exploded = 1;
		sfClock_restart(explode_time);
	}

	return exploded;
}

void explode_reset(void)
{
	exploded = 0;
}