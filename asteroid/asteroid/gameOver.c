#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "gameOver.h"

int game_over = 0;

void set_game_over(void)
{
	game_over = 1;
}

int is_game_over(void)
{
	return game_over;
}