
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "character.h"
#include <math.h>
#include "dt.h"
#include "gameOver.h"
#include "print.h"
#include "spaceship.h"

#define PI 3.141592

int angle = 360 - 90;
int can_move = 0;

character asteroid = { // definie la structure asteroid
	.vie = 3,
	.sprite = 0,
	.sprite_size = {0, 0},
	.texture = 0,
	.position = {(float)1920 / 2, (float)1080 / 2},
	.previous_position = {(float)1920 / 2, (float)1080 / 2},
	.speed = 0,
	.speed_max = 0.5f,
	.acceleration = .01f,
	.deceleration = .99f,
	.direction = {0, 0},
	.scale = {0.15f, 0.15f},
	.origin = {1, 1},
	.rotation = 0
};
int tuto_bool[] = { 1, 1, 1, 1 };
float time_tuto = 0;
void tuto(sfRenderWindow* window)
{
	if(tuto_bool[0])
	{
		print_str("Watch out, spaceships are attacking!", 30, (sfVector2f) { 1920.0f / 2, 200 }, sfWhite, window, NULL);
		print_str("[Q]/[LEFT] and [D]/[RIGHT]", 30, (sfVector2f) { 1920.0f / 2, 300 }, sfWhite, window, NULL);
		print_str("SHOOT : [space]", 30, (sfVector2f) { 1920.0f / 2, 400 }, sfWhite, window, NULL);
	}else if(tuto_bool[1])
	{
		print_str("Congrats ! You can now move.", 30, (sfVector2f) { 1920.0f / 2, 200 }, sfWhite, window, NULL);
		print_str("MOVE : [z]/[UP]", 30, (sfVector2f) { 1920.0f / 2, 300 }, sfWhite, window, NULL);

	}else if(tuto_bool[2])
	{
		print_str("you can pause the game.", 30, (sfVector2f) { 1920.0f / 2, 200 }, sfWhite, window, NULL);
		print_str("PAUSE : [ESCAPE]", 30, (sfVector2f) { 1920.0f / 2, 300 }, sfWhite, window, NULL);
		if(sfKeyboard_isKeyPressed(sfKeyEscape))
		{
			tuto_bool[2] = 0;
		}
	}else if(tuto_bool[3])
	{
		if (time_tuto < 5)
		{
			time_tuto += return_dt() / 1000;
			print_str("You can use your special ability ! (risky)", 30, (sfVector2f) { 1920.0f / 2, 200 }, sfWhite, window, NULL);
			print_str("EXPLODE : [SHIFT]", 30, (sfVector2f) { 1920.0f / 2, 300 }, sfWhite, window, NULL);
		}
	}
}

void set_tuto(const int tuto, const int state)
{
	tuto_bool[tuto] = state;
}

void create_sprite(sfSprite* sprite, const sfTexture* texture, const sfVector2f origin, const sfVector2f scale, const float rotation, const sfVector2f position) { // initialise un sprite
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setOrigin(sprite, origin);
	sfSprite_setScale(sprite, scale);
	sfSprite_setRotation(sprite, rotation);
	sfSprite_setPosition(sprite, position);
}

void move_character(character* asteroide_move, sfRenderWindow* window) { // deplace un character
	if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) { // fait tourner le personnage dans le sens horaire
		angle += 5;
		if (angle > 360) {// fait un cercle
			angle = 0;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) { // et dans le sens anti horaire
		angle -= 5;
		if (angle < 0) {
			angle = 360;
		}
	}

	sfVector2f impulse = { 0, 0 };

	if ((sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) && is_can_move()) { // fait avancer le personnage avec de l'inertie
		tuto_bool[1] = 0;
		if (asteroide_move->speed < asteroide_move->speed_max) { // tant que le personnage a une vitese inferieure a la vitesse max
			impulse.x = (float)cos(angle * PI / 180) * asteroide_move->acceleration * return_dt(); // creer une force a donner a son personnage
			impulse.y = (float)sin(angle * PI / 180) * asteroide_move->acceleration * return_dt();
		}
	}
	asteroide_move->direction.x *= asteroide_move->deceleration; //applique une deceleration continue qui freine l'asteroide
	asteroide_move->direction.y *= asteroide_move->deceleration;

	asteroide_move->direction.x += impulse.x;// donne cette force a la direction du personnage
	asteroide_move->direction.y += impulse.y;

	asteroide_move->previous_position.x = asteroide_move->position.x; // pour le calcule de la vitesse
	asteroide_move->previous_position.y = asteroide_move->position.y;

	asteroide_move->position.x += asteroide_move->direction.x; // applique la force dans la direction a la position du personnage
	asteroide_move->position.y += asteroide_move->direction.y;

	asteroide_move->speed = (float)(sqrt(pow(asteroide_move->previous_position.x - asteroide_move->position.x, 2) + pow(asteroide_move->previous_position.y - asteroide_move->position.y, 2))) / return_dt(); // calcule de la vitesse en temps reel du personnage

	if (asteroide_move->position.x > 1920 + 120) { // wrap around
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
	create_sprite(asteroide_move->sprite, asteroide_move->texture, asteroide_move->origin, asteroide_move->scale, (float)angle, asteroide_move->position); // applique tous les changements au sprite pour l'actualiser à l'écran
	sfRenderWindow_drawSprite(window, asteroide_move->sprite, NULL);
	sfSprite_setPosition(asteroide_move->sprite, asteroide_move->position);
}

void update_life(void) // fait perdre une vie au joueur
{
	if (collision_spaceship())// si le joueur touche un vaisseau
	{
		if (asteroid.vie > 1) // si le joueur a toujours une vie
		{
			asteroid.vie--; // retire une vie au joueur
			asteroid.position = (sfVector2f){ (int)1920 / 2, (int)1080 / 2 }; // reset sa position et la force appliquee a celui ci
			asteroid.direction = (sfVector2f){ 0, 0 };
			reset_pos_spaceship(); // reset la position de tous les vaisseaux
		}
		else
		{
			set_game_over(); // si le joueur n'a plus de vie, le jeu se met en game over
		}
	}
}

int is_can_move(void)
{
	return can_move;
}

void set_can_move(const int state)
{
	can_move = state;
}


void reset_character(void)
{
	angle = 360 - 90;
	can_move = 0;
	asteroid.sprite = sfSprite_create();
	asteroid.texture = sfTexture_createFromFile("sprites/spriteAsteroid.png", NULL);
	asteroid.sprite_size = (sfVector2f){ 1024, 1024 };
	asteroid.origin = (sfVector2f){ asteroid.sprite_size.x / 2, asteroid.sprite_size.y / 2 };
	asteroid.position.x = 1920.0f/2; asteroid.position.y = 1080.0f/2;
	asteroid.vie = 3;
	asteroid.previous_position = (sfVector2f){ (float)1920 / 2, (float)1080 / 2 };
	asteroid.speed = 0;
	asteroid.speed_max = 0.5f;
	asteroid.acceleration = .01f;
	asteroid.deceleration = .99f;
	asteroid.direction = (sfVector2f){ 0, 0 };
	asteroid.scale = (sfVector2f){ 0.15f, 0.15f };
	asteroid.rotation = 0;
	create_sprite(asteroid.sprite, asteroid.texture, asteroid.origin, asteroid.scale, -90, asteroid.position);
}