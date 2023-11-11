#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "spaceship.h"

#include <math.h>

#include "character.h"
#include "shoot.h"

#define PI 3.141592



int get_random_number(const int min, const int max) {
	return min + rand() % (max - min + 1);
}
int zone_x[4] = {0};
int zone_y[4] = {0};
void create_spaceship(void)
{
	zone_x[0] = get_random_number(-120, 1920 + 120);
	zone_x[1] = get_random_number(1920, 1920 + 120);
	zone_x[2] = get_random_number(-120, 1920 + 120);
	zone_x[3] = get_random_number(-120, 0);

	zone_y[0] = get_random_number(-120, 0);
	zone_y[1] = get_random_number(-120, 1080 + 120);
	zone_y[2] = get_random_number(1080, 1080 + 120);
	zone_y[3] = get_random_number(-120, 1080 + 120);

	const int zone = get_random_number(0, 4);

	for(int i = 0; i < 5; i++)
	{
		spaceship[i].direction = (sfVector2f){ 0, 0 };
		spaceship[i].origin = (sfVector2f){ 1, 1 };
		spaceship[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
		spaceship[i].previous_position = spaceship[i].position;
		spaceship[i].rotation = 0;
		spaceship[i].scale = (sfVector2f){ .2f, .2f };
		spaceship[i].speed = 5;
		spaceship[i].sprite = sfSprite_create();
		spaceship[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);

		spaceship[i].rotation = get_random_number(0, 360);
		spaceship[i].direction = (sfVector2f){ (float)cos(spaceship[i].rotation * PI / 180) , (float)sin(spaceship[i].rotation * PI / 180) };
		spaceship[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };

		sfSprite_setOrigin(spaceship[i].sprite, spaceship[i].origin);
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
		sfSprite_setRotation(spaceship[i].sprite, (float)spaceship[i].rotation + 90);
		sfSprite_setScale(spaceship[i].sprite, spaceship[i].scale);
		sfSprite_setTexture(spaceship[i].sprite, spaceship[i].texture, sfFalse);
	}
}

int created = 0;
int destroyed = 0;
int min_to_display_spaceship = 0;
void spawn_spaceship(sfRenderWindow* window) {
	if(created == 0)
	{
		created = 1;
		create_spaceship();
	}
	for(int i = 0; i < 5; i++)
	{
		spaceship[i].position.x += spaceship[i].direction.x * spaceship[i].speed;
		spaceship[i].position.y += spaceship[i].direction.y * spaceship[i].speed;
		if (spaceship[i].position.x > 1920 + 120)
		{
			spaceship[i].position.x = -120;
		}
		if (spaceship[i].position.x < -120)
		{
			spaceship[i].position.x = 1920 + 120;
		}

		if (spaceship[i].position.y > 1080 + 120)
		{
			spaceship[i].position.y = -120;
		}
		if (spaceship[i].position.y < -120)
		{
			spaceship[i].position.y = 1080 + 120;
		}
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
		sfRenderWindow_drawSprite(window, spaceship[i].sprite, NULL);
	}
	for(int i = 0; i<5; i++)
	{
		if (collision(window, i))
		{
			spaceship[i].position = (sfVector2f){ INFINITY, INFINITY };
			min_to_display++;
		}
	}
}