#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  {
	int vie;
	sfSprite* sprite;
	sfVector2f spriteSize;
	sfTexture* texture;
	sfVector2f position;
	sfVector2f previousPosition;
	float speed;
	float speedMax;
	float acceleration;
	float deceleration;
	sfVector2f direction;
	sfVector2f scale;
	sfVector2f origin;
	float rotation;
}character;

character asteroide;
int angle;

void moveCharacter(character* asteroide, sfWindow* window);
void createSprite(sfSprite* sprite, sfTexture* texture, sfVector2f origin, sfVector2f scale, float rotation, sfVector2f position);