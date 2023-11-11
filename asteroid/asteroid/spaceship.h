#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "character.h"

void create_spaceship(character* spaceship_to_create);
void spawn_spaceship(sfRenderWindow* window);
character spaceship[5];
character spaceship_average[10];
character spaceship_little[20];

#endif
