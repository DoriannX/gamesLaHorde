
#include "gameOver.h"

int game_over = 0;

void set_game_over(void) // met l'etat de game over pour le jeu
{
	game_over = 1;
}

int is_game_over(void)
{
	return game_over; // retourne si le jeu est en etat de game over ou pas
}

void reset_game_over(void)
{
	game_over = 0;
}