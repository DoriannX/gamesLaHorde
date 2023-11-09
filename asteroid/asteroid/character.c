#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "character.h"
#include <math.h>
#include "print.h"
#include "dt.h"

#define PI 3.141592 


int angle = -90;
character moveCharacter(character* asteroide, sfWindow* window){ // deplace un character
	if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) {
		angle += 5;
	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) {
		angle -= 5;
	}

	sfVector2f impulse = { 0, 0 };

	if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
		if (asteroide->speed < asteroide->speedMax) {
			impulse.x = cos(angle * PI / 180) * asteroide->acceleration * dt;
			impulse.y = sin(angle * PI / 180) * asteroide->acceleration * dt;
		}
	}
	asteroide->direction.x *= asteroide->deceleration;
	asteroide->direction.y *= asteroide->deceleration;

	asteroide->direction.x += impulse.x;
	asteroide->direction.y += impulse.y;

	asteroide->previousPosition.x = asteroide->position.x;
	asteroide->previousPosition.y = asteroide->position.y;
	
	asteroide->position.x += asteroide->direction.x;
	asteroide->position.y += asteroide->direction.y;

	asteroide->speed = (sqrt(pow(asteroide->previousPosition.x - asteroide->position.x, 2) + pow(asteroide->previousPosition.y - asteroide->position.y, 2))) / dt;

	if (asteroide->position.x > 1920 + 120) {
		asteroide->position.x = -120;
	}
	if (asteroide->position.x < -120) {
		asteroide->position.x = 1920+120;
	}

	if (asteroide->position.y > 1080 + 120) {
		asteroide->position.y = -120;
	}
	if (asteroide->position.y < -120) {
		asteroide->position.y = 1080 + 120;
	}
	createSprite(asteroide->sprite, asteroide->texture, asteroide->origin, asteroide->scale, angle, asteroide->position);
	sfRenderWindow_drawSprite(window, asteroide->sprite, NULL);
	sfSprite_setPosition(asteroide->sprite, asteroide->position);
	return *asteroide;
}

void createSprite(sfSprite* sprite, sfTexture* texture, sfVector2f origin, sfVector2f scale, float rotation, sfVector2f position) { // initialise un sprite
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setOrigin(sprite, origin);
	sfSprite_setScale(sprite, scale);
	sfSprite_setRotation(sprite, rotation);
	sfSprite_setPosition(sprite, position);
}