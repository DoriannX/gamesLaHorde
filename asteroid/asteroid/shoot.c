#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <math.h>
#include "shoot.h"
#include "character.h"
#include "spaceship.h"

#define PI 3.141592

int nb_projectile = 0;
int min_to_display = 1;
int min_to_display_average = 1;
void create_projectile(void) {
		if (nb_projectile - min_to_display == -1) {
			sfClock_restart(life_time_shoot);
		}
		nb_projectile++;
		projectile[nb_projectile].color = sfWhite;
		projectile[nb_projectile].bounds.x = 15;
		projectile[nb_projectile].bounds.y = 5;
		projectile[nb_projectile].rectangle = sfRectangleShape_create();
		projectile[nb_projectile].speed = 20;
		projectile[nb_projectile].rotation = (float)angle;
		projectile[nb_projectile].direction.x = (float)cos(angle * PI / 180);
		projectile[nb_projectile].direction.y = (float)sin(angle * PI / 180);
		projectile[nb_projectile].position = asteroid.position;

		sfRectangleShape_setFillColor(projectile[nb_projectile].rectangle, sfWhite);
		sfRectangleShape_setRotation(projectile[nb_projectile].rectangle, projectile[nb_projectile].rotation);
		sfRectangleShape_setSize(projectile[nb_projectile].rectangle, projectile[nb_projectile].bounds);
		sfRectangleShape_setOrigin(projectile[nb_projectile].rectangle, (sfVector2f) { projectile[nb_projectile].bounds.x / 2, projectile[nb_projectile].bounds.y / 2 });
		sfRectangleShape_setPosition(projectile[nb_projectile].rectangle, projectile[nb_projectile].position);
}


int collision(sfRenderWindow* window, const int j, const char* size)
{
	if(size == "big")
	{
		int collision_box[5] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++)
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship[j].position.x) <= 100 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship[j].position.y) <= 100;
			if (collision_box[j])
			{
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position);
				min_to_display++;
				break;
			}
		}
		return collision_box[j];
	}else if(size == "average")
	{
		int collision_box[10] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++)
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship_average[j].position.x) <= 50 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship_average[j].position.y) <= 50;
			if (collision_box[j])
			{
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position);
				min_to_display++;
				break;
			}
		}
		return collision_box[j];
	}
	else if(size == "small")
	{
		int collision_box[20] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++)
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship_small[j].position.x) <= 15 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship_small[j].position.y) <= 15;
			if (collision_box[j])
			{
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position);
				min_to_display++;
				break;
			}
		}
		return collision_box[j];
	}else
	{
		return 0;
	}

}

void shoot(sfRenderWindow* window) {
	if (sfTime_asSeconds(sfClock_getElapsedTime(life_time_shoot)) > .6f) {
		if (nb_projectile - min_to_display > -1) {
			sfClock_restart(life_time_shoot);
			min_to_display++;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeySpace)) {
		if (sfTime_asSeconds(sfClock_getElapsedTime(time_between_shoot)) > .5f) {
			if (nb_projectile - min_to_display == -1) {
				sfClock_restart(life_time_shoot);
			}
			sfClock_restart(time_between_shoot);
			if (nb_projectile < 9) {
				create_projectile();
			}
			else if (nb_projectile - min_to_display == -1) {
				nb_projectile = 0;
				min_to_display = 1;
				for (int i = 0; i < nb_projectile; i++) {
					sfRectangleShape_destroy(projectile[i].rectangle);
				}
				create_projectile();
			}
		}
	}
	for (int i = min_to_display; i <= nb_projectile; i++) {
		projectile[i].position.x += projectile[i].speed * projectile[i].direction.x;
		projectile[i].position.y += projectile[i].speed * projectile[i].direction.y;
		if (projectile[i].position.x > 1920 + 120) {
			projectile[i].position.x = -120;
		}
		if (projectile[i].position.x < -120) {
			projectile[i].position.x = 1920 + 120;
		}

		if (projectile[i].position.y > 1080 + 120) {
			projectile[i].position.y = -120;
		}
		if (projectile[i].position.y < -120) {
			projectile[i].position.y = 1080 + 120;
		}
		sfRectangleShape_setPosition(projectile[i].rectangle, projectile[i].position);
		sfRenderWindow_drawRectangleShape(window, projectile[i].rectangle, NULL);
	}
}