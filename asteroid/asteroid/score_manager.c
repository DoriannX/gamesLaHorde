
#include "score_manager.h"

int score = 0;

void add_score(const int nb_point) // ajout les points au score
{
	score += nb_point;
}

int return_score(void) // retourne le score actuelle
{
	return score;
}