#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

#include "level_manager.h"

#include "spaceship.h"

int actual_level = 0;
int leveling = 0;

void next_level(void)
{
	leveling = 1;
	actual_level ++;
	reset_spaceship();
	reset_leveling();
}

int get_actual_level(void)
{
	return actual_level;
}

int is_leveling(void)
{
	return leveling;
}

void reset_leveling(void)
{
	leveling = 0;
}