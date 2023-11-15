
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <math.h>
#include "shoot.h"
#include "character.h"
#include "dt.h"
#include "score_manager.h"
#include "spaceship.h"

#define PI 3.141592

typedef struct {
	sfVector2f position;
	sfVector2f previous_position;
	sfRectangleShape* rectangle;
	float speed;
	sfColor color;
	sfVector2f direction;
	sfVector2f bounds;
	sfVector2f origin;
	float rotation;
}object;

object projectile[10] = {0};

int nb_projectile = 0;
int min_to_display = 1;
void create_projectile(void) { // creer des projectiles
	if (nb_projectile - min_to_display == -1) {
		sfClock_restart(life_time_shoot);
	}
	nb_projectile++; // incremente le nombre de projectile
	projectile[nb_projectile].color = sfWhite; // creer les projectiles
	projectile[nb_projectile].bounds.x = 15;
	projectile[nb_projectile].bounds.y = 5;
	projectile[nb_projectile].rectangle = sfRectangleShape_create();
	projectile[nb_projectile].speed = (float)20/17;
	projectile[nb_projectile].rotation = (float)angle;
	projectile[nb_projectile].direction.x = (float)cos(angle * PI / 180);
	projectile[nb_projectile].direction.y = (float)sin(angle * PI / 180);
	projectile[nb_projectile].position = asteroid.position;

	sfRectangleShape_setFillColor(projectile[nb_projectile].rectangle, sfWhite); // actualise les projectile sur la window
	sfRectangleShape_setRotation(projectile[nb_projectile].rectangle, projectile[nb_projectile].rotation);
	sfRectangleShape_setSize(projectile[nb_projectile].rectangle, projectile[nb_projectile].bounds);
	sfRectangleShape_setOrigin(projectile[nb_projectile].rectangle, (sfVector2f) { projectile[nb_projectile].bounds.x / 2, projectile[nb_projectile].bounds.y / 2 });
	sfRectangleShape_setPosition(projectile[nb_projectile].rectangle, projectile[nb_projectile].position);
}

void destroy_projectile(void) // detruit tout quand c'est termine
{
	for(int i = min_to_display; i< nb_projectile; i++)
	sfRectangleShape_destroy(projectile[nb_projectile].rectangle);
}

int collision(sfRenderWindow* window, const int j, const char* size) // detecte les collisions
{
	if (size == "big") // si le vaisseau est gros
	{
		int collision_box[5] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++) // tous les vaisseaux
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship[j].position.x) <= 100 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship[j].position.y) <= 100;
			if (collision_box[j])//si un projectile touche un vaisseau
			{
				add_score(25); // ajout e25 au score
				if(!is_can_move())
				{
					set_can_move(1);
				}
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position); //ramene le projectile a la position du personnage
				min_to_display++; // reduit le nombre de projectile a afficher

				set_tuto(0, 0);
				break;
			}
		}
		return collision_box[j];
	}
	else if (size == "average") // si le vaisseau est moyen
	{
		int collision_box[10] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++)
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship_average[j].position.x) <= 50 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship_average[j].position.y) <= 50;
			if (collision_box[j])
			{
				add_score(50);
				if (!is_can_move())
				{
					set_can_move(1);
				}
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position);
				min_to_display++;

				set_tuto(0, 0);
				break;
			}
		}
		return collision_box[j];
	}
	else if (size == "small") // si le vaisseau est petit
	{
		int collision_box[20] = { 0 };
		for (int i = min_to_display; i <= nb_projectile; i++)
		{
			collision_box[j] = abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).x - (int)spaceship_small[j].position.x) <= 15 && abs((int)sfRectangleShape_getPosition(projectile[i].rectangle).y - (int)spaceship_small[j].position.y) <= 15;
			if (collision_box[j])
			{
				add_score(100);
				if (!is_can_move())
				{
					set_can_move(1);
				}
				sfRectangleShape_setPosition(projectile[i].rectangle, asteroid.position);
				min_to_display++;

				set_tuto(0, 0);
				break;
			}
		}
		return collision_box[j];
	}
	else // si quelque chose se passe mal return 0
	{
		return 0;
	}
}

void shoot(sfRenderWindow* window) { // permet au joueur de tirer
	if (sfTime_asSeconds(sfClock_getElapsedTime(life_time_shoot)) > .6f) { // la balle reste affiche 0.6 seconde
		if (nb_projectile - min_to_display > -1) {
			sfClock_restart(life_time_shoot);
			min_to_display++;
		}
	}
	if (sfKeyboard_isKeyPressed(sfKeySpace)) {
		if (sfTime_asSeconds(sfClock_getElapsedTime(time_between_shoot)) > .5f) { // le joueur peut tirer un projectile toutes les 0.5 seconde
			if (nb_projectile - min_to_display == -1) {
				sfClock_restart(life_time_shoot);
			}
			sfClock_restart(time_between_shoot);
			if (nb_projectile < 9) { // quand le nombre de projectile arrive a 9, le vaisseau doit recharger
				create_projectile();
			}
			if (nb_projectile - min_to_display == -1) { // quand il n'y a plus de balle affiche, le vaisseau a fini de recharger
				nb_projectile = 0;
				min_to_display = 1;
				create_projectile();
			}
		}
	}
	for (int i = min_to_display; i <= nb_projectile; i++) {
		projectile[i].position.x += projectile[i].speed * projectile[i].direction.x * return_dt(); 
		projectile[i].position.y += projectile[i].speed * projectile[i].direction.y * return_dt();
		if (projectile[i].position.x > 1920 + 120) { // wrap around
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
		sfRectangleShape_setPosition(projectile[i].rectangle, projectile[i].position); //actualise le tout sur la window
		sfRenderWindow_drawRectangleShape(window, projectile[i].rectangle, NULL);
	}
}

void reset_shoot(void)
{
	for(int i = 0; i< 10; i++)
	{
		projectile[i].position = (sfVector2f){ 0, 0 };
		projectile[i].rectangle = NULL;
		projectile[i].speed = 0;
		projectile[i].direction = (sfVector2f){0, 0};
		projectile[i].bounds = (sfVector2f){ 0, 0 };
		projectile[i].color = sfWhite;
		projectile[i].origin = (sfVector2f){ 0, 0 };
		projectile[i].previous_position = (sfVector2f){ 0, 0, };
		projectile[i].rotation = 0;
	}

	nb_projectile = 0;
	min_to_display = 1;
	sfClock_restart(life_time_shoot);
	sfClock_restart(time_between_shoot);
	
}