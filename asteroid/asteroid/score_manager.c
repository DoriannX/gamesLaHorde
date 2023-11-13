#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "score_manager.h"

#include "print.h"

int score = 0;

void add_score(const int nb_point)
{
	score+= nb_point;
}

int return_score(void)
{
	return score;
}