
#include <SFML/System.h>
#include "dt.h"

sfTime previous_frame = { 0 };
sfTime now = { 0 };
float dt = 0;
void delta_time(void) { // actualise le delta temps
	now = sfClock_getElapsedTime(beginning);
	dt = (float)(sfTime_asMilliseconds(now) - sfTime_asMilliseconds(previous_frame));
	previous_frame = now;
}

float return_dt(void) // retourne le dt en temps reel
{
	return dt;
}

void reset_dt(void) // reset le dt quand la partie est recommence
{
	previous_frame = (sfTime){ 0 };
	now = (sfTime){ 0 };
	dt = 0;
}