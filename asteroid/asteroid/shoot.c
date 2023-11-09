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

bool shooted = false;



//object createProjectile() {
//	object projectileTemp = {
//		.color = sfWhite,
//		.direction = asteroide.direction,
//		.bounds.x = 15,
//		.bounds.y = 5,
//		.position = asteroide.position,
//		.previousPosition = projectile.position,
//		.rectangle = sfRectangleShape_create(),
//		.rotation = angle,
//		.speed = 50
//	}
//	
//	return projectileTemp;
//}


void shoot(sfWindow* window) {
	if (sfKeyboard_isKeyPressed(sfKeySpace)) {
		//createProjectile();
		shooted = true;
		projectile.direction.x = cos(angle * PI / 180);
		projectile.direction.y = sin(angle * PI / 180);
		projectile.position = asteroide.position;
		projectile.previousPosition = projectile.position;
		projectile.rotation = angle;
		sfRectangleShape_setRotation(projectile.rectangle, projectile.rotation);
	}
	if (shooted) {
		projectile.position.x += projectile.speed * projectile.direction.x;
		projectile.position.y += projectile.speed * projectile.direction.y;
		sfRectangleShape_setPosition(projectile.rectangle, projectile.position);
		sfRenderWindow_drawRectangleShape(window, projectile.rectangle, NULL);
	}
}