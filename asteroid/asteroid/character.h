#ifndef CHARACTER_H
#define CHARACTER_H
typedef struct {
	int vie;
	sfSprite* sprite;
	sfVector2f sprite_size;
	sfTexture* texture;
	sfVector2f position;
	sfVector2f previous_position;
	float speed;
	float speed_max;
	float acceleration;
	float deceleration;
	sfVector2f direction;
	sfVector2f scale;
	sfVector2f origin;
	int rotation;
	int little;
}character;

character asteroid;
int angle;

void move_character(character* asteroide_move, sfRenderWindow* window);
void create_sprite(sfSprite* sprite, sfTexture* texture, sfVector2f origin, sfVector2f scale, float rotation, sfVector2f position);
void lose_life(sfRenderWindow* window);
#endif
