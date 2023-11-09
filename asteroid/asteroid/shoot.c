#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "shoot.h"
#include "character.h"
#include "print.h"
#include <stdbool.h>

#define PI 3.141592 

int nbProjectile = 0;


int minToDisplay = 1;
void createProjectile() {
		if (nbProjectile - minToDisplay == -1) {
			sfClock_restart(lifeTimeShoot);
		}
		nbProjectile++;
		projectile[nbProjectile].color = sfWhite;
		projectile[nbProjectile].bounds.x = 15;
		projectile[nbProjectile].bounds.y = 5;
		projectile[nbProjectile].rectangle = sfRectangleShape_create();
		projectile[nbProjectile].speed = 5;
		projectile[nbProjectile].rotation = angle;
		projectile[nbProjectile].direction.x = cos(angle * PI / 180);
		projectile[nbProjectile].direction.y = sin(angle * PI / 180);
		projectile[nbProjectile].position = asteroide.position;

		sfRectangleShape_setFillColor(projectile[nbProjectile].rectangle, sfWhite);
		sfRectangleShape_setRotation(projectile[nbProjectile].rectangle, projectile[nbProjectile].rotation);
		sfRectangleShape_setSize(projectile[nbProjectile].rectangle, projectile[nbProjectile].bounds);
		sfRectangleShape_setOrigin(projectile[nbProjectile].rectangle, (sfVector2f) { projectile[nbProjectile].bounds.x / 2, projectile[nbProjectile].bounds.y / 2 });
		sfRectangleShape_setPosition(projectile[nbProjectile].rectangle, projectile[nbProjectile].position);
}

void shoot(sfWindow* window) {
	if (sfTime_asSeconds(sfClock_getElapsedTime(lifeTimeShoot)) > 1) {
		if (nbProjectile - minToDisplay > -1) {
			sfClock_restart(lifeTimeShoot);
			minToDisplay++;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeySpace)) {
		if (sfTime_asSeconds(sfClock_getElapsedTime(timeBetweenShoot)) > .5f) {
			if (nbProjectile - minToDisplay == -1) {
				sfClock_restart(lifeTimeShoot);
			}
			sfClock_restart(timeBetweenShoot);
			if (nbProjectile < 9) {
				createProjectile();
			}
			else if (nbProjectile - minToDisplay == -1) {
				nbProjectile = 0;
				minToDisplay = 1;
			}
		}
	}
	for (int i = minToDisplay; i <= nbProjectile; i++) {
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