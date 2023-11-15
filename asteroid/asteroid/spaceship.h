#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "character.h"

void create_spaceship(void);
void spawn_spaceship(sfRenderWindow* window);
character spaceship[5];
character spaceship_average[10];
character spaceship_small[20];
int collision_spaceship(void);
void reset_pos_spaceship(void);
void destroy_spaceship(void);
void reset_spaceship(void);
void set_difficulty(const int diff);
void update_speed(void);

#endif
