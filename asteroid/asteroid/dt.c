#include <SFML/System.h>
#include "dt.h"

sfTime previous_frame = { 0 };
sfTime now = { 0 };

void delta_time(void) {
	now = sfClock_getElapsedTime(beginning);
	dt = sfTime_asMilliseconds(now) - sfTime_asMilliseconds(previous_frame);
	previous_frame = now;
}