#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"
#include "dt.h"

sfTime previousFrame = { 0 };
sfTime now = { 0 };

void deltaTime() {
	now = sfClock_getElapsedTime(beginning);
	dt = sfTime_asMilliseconds(now) - sfTime_asMilliseconds(previousFrame);
	previousFrame = now;
}