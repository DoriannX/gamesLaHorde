#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "spaceship.h"

#include <math.h>

#include "character.h"
#include "print.h"
#include "shoot.h"
#include "special_attack.h"

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
		spaceship[i].origin = (sfVector2f){ 1, 1 };
		spaceship[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
		spaceship[i].previous_position = spaceship[i].position;
		spaceship[i].scale = (sfVector2f){ .2f, .2f };
		spaceship[i].speed = 2;
		spaceship[i].sprite = sfSprite_create();
		spaceship[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship[i].rotation = get_random_number(0, 360);
		spaceship[i].direction = (sfVector2f){ (float)cos(spaceship[i].rotation * PI / 180) , (float)sin(spaceship[i].rotation * PI / 180) };
		spaceship[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship[i].little = 0;

		sfSprite_setOrigin(spaceship[i].sprite, spaceship[i].origin);
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
		sfSprite_setRotation(spaceship[i].sprite, (float)spaceship[i].rotation + 90);
		sfSprite_setScale(spaceship[i].sprite, spaceship[i].scale);
		sfSprite_setTexture(spaceship[i].sprite, spaceship[i].texture, sfFalse);

		
	}
	for (int i = 0; i < 10; i++)
	{
		spaceship_average[i].origin = (sfVector2f){ 1, 1 };
		spaceship_average[i].previous_position = spaceship_average[i].position;
		spaceship_average[i].position = spaceship[i/2].position;
		spaceship_average[i].scale = (sfVector2f){ .1f, .1f };
		spaceship_average[i].speed = 4;
		spaceship_average[i].sprite = sfSprite_create();
		spaceship_average[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship_average[i].rotation = get_random_number(0, 360);
		spaceship_average[i].direction = (sfVector2f){ (float)cos(spaceship_average[i].rotation * PI / 180) , (float)sin(spaceship_average[i].rotation * PI / 180) };
		spaceship_average[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship_average[i].little = 0;

		sfSprite_setOrigin(spaceship_average[i].sprite, spaceship_average[i].origin);
		sfSprite_setPosition(spaceship_average[i].sprite, spaceship_average[i].position);
		sfSprite_setRotation(spaceship_average[i].sprite, (float)spaceship_average[i].rotation + 90);
		sfSprite_setScale(spaceship_average[i].sprite, spaceship_average[i].scale);
		sfSprite_setTexture(spaceship_average[i].sprite, spaceship_average[i].texture, sfFalse);
	}
	for (int i = 0; i < 20; i++)
	{
		spaceship_small[i].direction = (sfVector2f){ 0, 0 };
		spaceship_small[i].origin = (sfVector2f){ 1, 1 };
		spaceship_small[i].position = spaceship_average[i/2].position;
		spaceship_small[i].previous_position = spaceship_small[i].position;
		spaceship_small[i].rotation = 0;
		spaceship_small[i].scale = (sfVector2f){ .05f, .05f };
		spaceship_small[i].speed = 6;
		spaceship_small[i].sprite = sfSprite_create();
		spaceship_small[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship_small[i].rotation = get_random_number(0, 360);
		spaceship_small[i].direction = (sfVector2f){ (float)cos(spaceship_small[i].rotation * PI / 180) , (float)sin(spaceship_small[i].rotation * PI / 180) };
		spaceship_small[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship_small[i].little = 0;

		sfSprite_setOrigin(spaceship_small[i].sprite, spaceship_small[i].origin);
		sfSprite_setPosition(spaceship_small[i].sprite, spaceship_small[i].position);
		sfSprite_setRotation(spaceship_small[i].sprite, (float)spaceship_small[i].rotation + 90);
		sfSprite_setScale(spaceship_small[i].sprite, spaceship_small[i].scale);
		sfSprite_setTexture(spaceship_small[i].sprite, spaceship_small[i].texture, sfFalse);
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
	for (int j = 0; j < 20; j++)
	{
		if (spaceship_average[j / 2].little)
		{
			if (!spaceship_small[j].little)
			{
				spaceship_small[j].position.x += spaceship_small[j].direction.x * spaceship_small[j].speed;
				spaceship_small[j].position.y += spaceship_small[j].direction.y * spaceship_small[j].speed;
				if (spaceship_small[j].position.x > 1920 + 120)
				{
					spaceship_small[j].position.x = -120;
				}
				if (spaceship_small[j].position.x < -120)
				{
					spaceship_small[j].position.x = 1920 + 120;
				}

				if (spaceship_small[j].position.y > 1080 + 120)
				{
					spaceship_small[j].position.y = -120;
				}
				if (spaceship_small[j].position.y < -120)
				{
					spaceship_small[j].position.y = 1080 + 120;
				}
				sfSprite_setPosition(spaceship_small[j].sprite, spaceship_small[j].position);
			}
		}
		else
		{
			spaceship_small[j].position = spaceship_average[j / 2].position;
			sfSprite_setPosition(spaceship_small[j].sprite, spaceship_average[j/2].position);
		}
		if (!spaceship_small[j].little)
		{
			sfRenderWindow_drawSprite(window, spaceship_small[j].sprite, NULL);
		}
		if (collision(window, j, "small") || (explode(window) && spaceship_average[j/2].little))
		{
			spaceship_small[j].position = (sfVector2f){ INFINITY, INFINITY };
			spaceship_small[j].little = 1;
			if (j >= 19)
				explode_reset();
		}
	}
	for (int j = 0; j < 10; j++)
	{
		if (spaceship[j / 2].little)
		{
			if (!spaceship_average[j].little)
			{
				spaceship_average[j].position.x += spaceship_average[j].direction.x * spaceship_average[j].speed;
				spaceship_average[j].position.y += spaceship_average[j].direction.y * spaceship_average[j].speed;
				if (spaceship_average[j].position.x > 1920 + 120)
				{
					spaceship_average[j].position.x = -120;
				}
				if (spaceship_average[j].position.x < -120)
				{
					spaceship_average[j].position.x = 1920 + 120;
				}

				if (spaceship_average[j].position.y > 1080 + 120)
				{
					spaceship_average[j].position.y = -120;
				}
				if (spaceship_average[j].position.y < -120)
				{
					spaceship_average[j].position.y = 1080 + 120;
				}
				sfSprite_setPosition(spaceship_average[j].sprite, spaceship_average[j].position);
			}
		}
		else
		{
			spaceship_average[j].position = spaceship[j / 2].position;
			sfSprite_setPosition(spaceship_average[j].sprite, spaceship_average[j].position);
		}
		if (!spaceship_average[j].little)
		{
			sfRenderWindow_drawSprite(window, spaceship_average[j].sprite, NULL);
		}
		if (collision(window, j, "average") || (explode(window) && spaceship[j / 2].little))
		{
			spaceship_average[j].position = (sfVector2f){ INFINITY, INFINITY };
			spaceship_average[j].little = 1;
			if (j >= 9)
				explode_reset();
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if(!spaceship[i].little)
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
			if (!spaceship[i].little)
			{
				sfRenderWindow_drawSprite(window, spaceship[i].sprite, NULL);
			}
			print_int((explode(window)), 24, (sfVector2f) { 100, 200 }, sfWhite, window); 
			if (collision(window, i, "big") || explode(window))
			{
				spaceship[i].position = (sfVector2f){ INFINITY, INFINITY };
				spaceship[i].little = 1;
				if(i >= 4)
					explode_reset();
			}
		}
	}
}

int collision_spaceship(void)
{
	int collided_spaceship = 0;

	int collision_box_big = 0;
	int collision_box_average = 0;
	int collision_box_small = 0;
	for(int i = 0; i < 20; i++)
	{
		collision_box_small = abs((int)asteroid.position.x - (int)spaceship_small[i].position.x) <= 50 && abs((int)asteroid.position.y - (int)spaceship_small[i].position.y) <= 50;
		if (collision_box_small)
			break;
	}
	for(int i = 0; i<10; i++)
	{
		collision_box_average = abs((int)asteroid.position.x - (int)spaceship_average[i].position.x) <= 70 && abs((int)asteroid.position.y - (int)spaceship_average[i].position.y) <= 70;
		if (collision_box_average)
			break;
	}
	for (int i = 0; i < 5; i++)
	{
		collision_box_big = abs((int)asteroid.position.x - (int)spaceship[i].position.x) <= 130 && abs((int)asteroid.position.y - (int)spaceship[i].position.y) <= 130;
		if (collision_box_big)
			break;
	}
	if (collision_box_big || collision_box_average || collision_box_small)
	{
		collided_spaceship = 1;
	}
	return collided_spaceship;
	
}