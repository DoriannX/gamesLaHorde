#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	sfVector2f position;
	sfVector2f previousPosition;
	sfRectangleShape* rectangle;
	sfColor color;
	float speed;
	sfVector2f direction;
	sfVector2f bounds;
	sfVector2f origin;
	float rotation;
}object;

object projectile;
