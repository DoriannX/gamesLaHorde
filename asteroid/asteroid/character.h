#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.h>
#include <SFML/System.h>
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
void update_life(void);
int is_can_move(void);
void set_can_move(const int state);
void reset_character(void);
void tuto(sfRenderWindow* window);
void set_tuto(const int tuto, const int state);

#endif
