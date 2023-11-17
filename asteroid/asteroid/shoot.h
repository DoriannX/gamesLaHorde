#ifndef SHOOT_H
#define SHOOT_H

#include <SFML/Graphics.h>
#include <SFML/System.h>

sfClock* time_between_shoot;
sfClock* life_time_shoot;
void shoot(sfRenderWindow* window);
int collision(sfRenderWindow* window, const int j, const int size);
void destroy_projectile(void);
void reset_shoot(void);
#endif
