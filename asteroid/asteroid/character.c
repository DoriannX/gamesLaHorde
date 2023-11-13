#include <SFML/Graphics.h>
#include <stdlib.h>
#include "character.h"
#include <math.h>
#include "dt.h"

#define PI 3.141592

int angle = 360 - 90;



void create_sprite(sfSprite* sprite, const sfTexture* texture, const sfVector2f origin, const sfVector2f scale, const float rotation, const sfVector2f position) { // initialise un sprite
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setOrigin(sprite, origin);
	sfSprite_setScale(sprite, scale);
	sfSprite_setRotation(sprite, rotation);
	sfSprite_setPosition(sprite, position);
}

void move_character(character* asteroide_move, sfRenderWindow* window) { // deplace un character
	if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) {
		angle += 5;
		if (angle > 360) {
			angle = 0;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) {
		angle -= 5;
		if (angle < 0) {
			angle = 360;
		}
	}

	sfVector2f impulse = { 0, 0 };

	if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
		if (asteroide_move->speed < asteroide_move->speed_max) {
			impulse.x = (float)cos(angle * PI / 180) * asteroide_move->acceleration * (float)dt;
			impulse.y = (float)sin(angle * PI / 180) * asteroide_move->acceleration * (float)dt;
		}
	}
	asteroide_move->direction.x *= asteroide_move->deceleration;
	asteroide_move->direction.y *= asteroide_move->deceleration;

	asteroide_move->direction.x += impulse.x;
	asteroide_move->direction.y += impulse.y;

	asteroide_move->previous_position.x = asteroide_move->position.x;
	asteroide_move->previous_position.y = asteroide_move->position.y;

	asteroide_move->position.x += asteroide_move->direction.x;
	asteroide_move->position.y += asteroide_move->direction.y;

	asteroide_move->speed = (float)(sqrt(pow(asteroide_move->previous_position.x - asteroide_move->position.x, 2) + pow(asteroide_move->previous_position.y - asteroide_move->position.y, 2))) / (float)dt;

	if (asteroide_move->position.x > 1920 + 120) {
		asteroide_move->position.x = -120;
	}
	if (asteroide_move->position.x < -120) {
		asteroide_move->position.x = 1920 + 120;
	}

	if (asteroide_move->position.y > 1080 + 120) {
		asteroide_move->position.y = -120;
	}
	if (asteroide_move->position.y < -120) {
		asteroide_move->position.y = 1080 + 120;
	}
	create_sprite(asteroide_move->sprite, asteroide_move->texture, asteroide_move->origin, asteroide_move->scale, (float)angle, asteroide_move->position);
	sfRenderWindow_drawSprite(window, asteroide_move->sprite, NULL);
	sfSprite_setPosition(asteroide_move->sprite, asteroide_move->position);
}