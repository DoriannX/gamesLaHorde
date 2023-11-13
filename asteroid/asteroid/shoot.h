#ifndef SHOOT_H
#define SHOOT_H

#include <SFML/Graphics.h>
#include <SFML/System.h>

typedef struct {
	sfVector2f position;
	sfVector2f previousPosition;
	sfRectangleShape* rectangle;
	float speed;
	sfColor color;
	sfVector2f direction;
	sfVector2f bounds;
	sfVector2f origin;
	float rotation;
}object;

int nb_projectile;
sfClock* time_between_shoot;
sfClock* life_time_shoot;
object projectile[10];
void shoot(sfRenderWindow* window);
int collision(sfRenderWindow* window, const int j, const char* size);
int min_to_display;
int min_to_display_average;
#endif

