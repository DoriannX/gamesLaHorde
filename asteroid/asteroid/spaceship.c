
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "spaceship.h"

#include <math.h>

#include "character.h"
#include "dt.h"
#include "level_manager.h"
#include "print.h"
#include "scale.h"
#include "shoot.h"
#include "special_attack.h"

#define PI 3.141592

int get_random_number(const int min, const int max) { // creer un nombre random
	return min + rand() % (max - min + 1);
}
int zone_x[4] = { 0 };
int zone_y[4] = { 0 };
int spaceship_exploded[5] = { 0 };
int spaceship_exploded_average[10] = { 0 };
int spaceship_exploded_little[20] = { 0 };
int difficulty = 0;
int zone = 0;
void get_random_pos(void)
{
	zone_x[0] = get_random_number((-120) * (int)scale_x, (1920 + 120) * (int)scale_x); // lui donne une position random en dehors de ce que le joueur peut voir
	zone_x[1] = get_random_number(1920 * (int)scale_x, (1920 + 120) * (int)scale_x);
	zone_x[2] = get_random_number((-120) * (int)scale_x, (1920 + 120) * (int)scale_x);
	zone_x[3] = get_random_number((-120) * (int)scale_x, 0);

	zone_y[0] = get_random_number((-120) * (int)scale_y, 0);
	zone_y[1] = get_random_number((-120) * (int)scale_y, (1080 + 120) * (int)scale_y);
	zone_y[2] = get_random_number(1080 * (int)scale_y, (1080 + 120) * (int)scale_y);
	zone_y[3] = get_random_number((-120) * (int)scale_y, (1080 + 120) * (int)scale_y);

	zone = get_random_number(0, 4);
	
}

void create_spaceship(void) // creer un vaisseau
{
	

	for (int i = 0; i < 5; i++)
	{
		get_random_pos(); // creer une position aleatoire

		spaceship[i].origin = (sfVector2f){ 1, 1 }; // creer un gros vaisseau
		spaceship[i].position = (sfVector2f){ (float)zone_x[zone], (float)zone_y[zone] };
		spaceship[i].previous_position = spaceship[i].position;
		spaceship[i].scale = (sfVector2f){ .3f * scale_x, .3f * scale_y };
		if(!is_leveling())
		{
			switch (difficulty)
			{
			case 1: spaceship[i].speed = (2.0f / 17) * scale_x; break; // en fonction de la difficulte met une vitesse
			case 2: spaceship[i].speed = (3.0f / 17) * scale_x; break;
			default: spaceship[i].speed = (1.0f / 17) * scale_x; break;
			}
		}
		spaceship[i].speed_max = spaceship[i].speed * 2;
		spaceship[i].sprite = sfSprite_create();
		spaceship[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship[i].rotation = get_random_number(0, 360);
		spaceship[i].direction = (sfVector2f){ (float)cos(spaceship[i].rotation * PI / 180) , (float)sin(spaceship[i].rotation * PI / 180) };
		spaceship[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship[i].little = 0;

		sfSprite_setOrigin(spaceship[i].sprite, spaceship[i].origin);
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
		sfSprite_setRotation(spaceship[i].sprite, (float)spaceship[i].rotation + 90);
		sfSprite_setScale(spaceship[i].sprite, spaceship[i].scale);
		sfSprite_setTexture(spaceship[i].sprite, spaceship[i].texture, sfFalse);
	}
	for (int i = 0; i < 10; i++)
	{
		spaceship_average[i].origin = (sfVector2f){ 1, 1 }; // creer un vaisseau de taille moyenne
		spaceship_average[i].previous_position = spaceship_average[i].position;
		spaceship_average[i].position = spaceship[i / 2].position;
		spaceship_average[i].scale = (sfVector2f){ .15f * scale_x, .15f* scale_y };
		if(!is_leveling())
		{
			switch (difficulty)
			{
			case 1: spaceship_average[i].speed = (3.0f / 17) * scale_x; break;
			case 2: spaceship_average[i].speed = (4.0f / 17) * scale_x; break;
			default: spaceship_average[i].speed = (2.0f / 17) * scale_x; break;
			}
		}
		spaceship_average[i].speed_max = spaceship_average[i].speed * 2;
		spaceship_average[i].sprite = sfSprite_create();
		spaceship_average[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship_average[i].rotation = get_random_number(0, 360);
		spaceship_average[i].direction = (sfVector2f){ (float)cos(spaceship_average[i].rotation * PI / 180) , (float)sin(spaceship_average[i].rotation * PI / 180) };
		spaceship_average[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship_average[i].little = 0;

		sfSprite_setOrigin(spaceship_average[i].sprite, spaceship_average[i].origin);
		sfSprite_setPosition(spaceship_average[i].sprite, spaceship_average[i].position);
		sfSprite_setRotation(spaceship_average[i].sprite, (float)spaceship_average[i].rotation + 90);
		sfSprite_setScale(spaceship_average[i].sprite, spaceship_average[i].scale);
		sfSprite_setTexture(spaceship_average[i].sprite, spaceship_average[i].texture, sfFalse);

	}
	for (int i = 0; i < 20; i++)
	{
		spaceship_small[i].direction = (sfVector2f){ 0, 0 }; // creer un vaisseau de petite taille
		spaceship_small[i].origin = (sfVector2f){ 1, 1 };
		spaceship_small[i].position = spaceship_average[i / 2].position;
		spaceship_small[i].previous_position = spaceship_small[i].position;
		spaceship_small[i].rotation = 0;
		spaceship_small[i].scale = (sfVector2f){ .1f * scale_x, .1f * scale_y };
		if(!is_leveling())
		{
			switch (difficulty)
			{
			case 1: spaceship_small[i].speed = (4.0f / 17) * scale_x; break;
			case 2: spaceship_small[i].speed = (5.0f / 17) * scale_x; break;
			default: spaceship_small[i].speed = (3.0f / 17) * scale_x; break;
			}
		}
		spaceship_small[i].speed_max = spaceship_small[i].speed * 2;
		spaceship_small[i].sprite = sfSprite_create();
		spaceship_small[i].texture = sfTexture_createFromFile("sprites/spriteSpaceship.png", NULL);
		spaceship_small[i].rotation = get_random_number(0, 360);
		spaceship_small[i].direction = (sfVector2f){ (float)cos(spaceship_small[i].rotation * PI / 180) , (float)sin(spaceship_small[i].rotation * PI / 180) };
		spaceship_small[i].origin = (sfVector2f){ (float)1024 / 2, (float)1024 / 2 };
		spaceship_small[i].little = 0;

		sfSprite_setOrigin(spaceship_small[i].sprite, spaceship_small[i].origin);
		sfSprite_setPosition(spaceship_small[i].sprite, spaceship_small[i].position);
		sfSprite_setRotation(spaceship_small[i].sprite, (float)spaceship_small[i].rotation + 90);
		sfSprite_setScale(spaceship_small[i].sprite, spaceship_small[i].scale);
		sfSprite_setTexture(spaceship_small[i].sprite, spaceship_small[i].texture, sfFalse);

	}
}

void update_speed(void) // quand la difficulte est change au milieu de la partie update la speed
{
	for (int i = 0; i < 5; i++)
	{
		switch (difficulty)
		{
		case 1: spaceship[i].speed = (2.0f / 17) * scale_x; spaceship[i].speed_max = spaceship[i].speed * 2; break;
		case 2: spaceship[i].speed = (3.0f / 17) * scale_x; spaceship[i].speed_max = spaceship[i].speed * 2; break;
		default: spaceship[i].speed = (1.0f / 17) * scale_x; spaceship[i].speed_max = spaceship[i].speed * 2; break;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		switch (difficulty)
		{
		case 1: spaceship_average[i].speed = (3.0f / 17) * scale_x; spaceship_average[i].speed_max = spaceship_average[i].speed * 2;  break;
		case 2: spaceship_average[i].speed =( 4.0f / 17) * scale_x; spaceship_average[i].speed_max = spaceship_average[i].speed * 2;  break;
		default: spaceship_average[i].speed = (2.0f / 17) * scale_x; spaceship_average[i].speed_max = spaceship_average[i].speed * 2;  break;

		}
	}
	for (int i = 0; i < 20; i++)
	{
		switch (difficulty)
		{
		case 1: spaceship_small[i].speed = (4.0f / 17) * scale_x; spaceship_small[i].speed_max = spaceship_small[i].speed * 2; break;
		case 2: spaceship_small[i].speed = (5.0f / 17) * scale_x; spaceship_small[i].speed_max = spaceship_small[i].speed * 2; break;
		default: spaceship_small[i].speed = (3.0f / 17) * scale_x; spaceship_small[i].speed_max = spaceship_small[i].speed * 2; break;
		}
	}
}

int collision_box = 0;
int collision_box_average = 0;
int collision_box_small = 0;
void collision_between_spaceships(sfRenderWindow* window)
{

	for(int i = 0; i<5;i++)
	{
		for(int j = 0; j < 5; j++) // gros contre gros
		{
			if (&spaceship[i].sprite != &spaceship[j].sprite)
				collision_box = abs((int)spaceship[i].position.x - (int)spaceship[j].position.x) < 200 * (int)scale_x && abs((int)spaceship[i].position.y - (int)spaceship[j].position.y) < 200 * (int)scale_y;

			if(collision_box)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship[i].position.x - spaceship[j].position.x, spaceship[i].position.y - spaceship[j].position.y };
				const double length_between_spaceships = sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / (float)length_between_spaceships, collision_vector.y / (float)length_between_spaceships };
				const float scalar_product_1 = spaceship[i].direction.x * collision_normal.x + spaceship[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship[j].direction.x * collision_normal.x + spaceship[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship[i].position.x += .01f*collision_vector.x;
				spaceship[i].position.y += .01f*collision_vector.y;
				spaceship[i].direction = rebound_vector_1;
				collision_box = 0;
				break;
			}
			}
		for (int j = 0; j < 10; j++) // gros contre moyen
		{	if(j / 2 != i)
				collision_box_average = abs((int)spaceship[i].position.x - (int)spaceship_average[j].position.x) <= 150 * (int)scale_x && abs((int)spaceship[i].position.y - (int)spaceship_average[j].position.y) <= 150 * (int)scale_y;

			if (collision_box_average)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship_average[j].position.x - spaceship[i].position.x, spaceship_average[j].position.y - spaceship[i].position.y };
				const float length_between_spaceships = (float)sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / length_between_spaceships, collision_vector.y / length_between_spaceships };
				const float scalar_product_1 = spaceship[i].direction.x * collision_normal.x + spaceship[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship_average[j].direction.x * collision_normal.x + spaceship_average[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship_average[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship_average[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship[i].direction = rebound_vector_1;
				spaceship_average[j].direction = rebound_vector_2;
				spaceship_average[i].position.x += .01f * collision_vector.x;
				spaceship_average[i].position.y += .01f * collision_vector.y;
				collision_box_average = 0;
				break;
			}
		}
		for (int j = 0; j < 20; j++) // gros contre petit
		{
			if (j/4 != i)
				collision_box_small = abs((int)spaceship[i].position.x - (int)spaceship_small[j].position.x) <= 100 * (int)scale_x && abs((int)spaceship[i].position.y - (int)spaceship_small[j].position.y) <= 100 * (int)scale_y;

			if (collision_box_small)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship_small[j].position.x - spaceship[i].position.x, spaceship_small[j].position.y - spaceship[i].position.y };
				const float length_between_spaceships = (float)sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / length_between_spaceships, collision_vector.y / length_between_spaceships };
				const float scalar_product_1 = spaceship[i].direction.x * collision_normal.x + spaceship[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship_small[j].direction.x * collision_normal.x + spaceship_small[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship_small[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship_small[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship[i].direction = rebound_vector_1;
				spaceship_small[j].direction = rebound_vector_2;
				spaceship_small[i].position.x += .01f * collision_vector.x;
				spaceship_small[i].position.y += .01f * collision_vector.y;
				collision_box_small = 0;
				break;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) // gros contre moyen
		{
			if (j / 2 != i)
				collision_box_average = abs((int)spaceship_average[i].position.x - (int)spaceship_average[j].position.x) <= 150 * (int)scale_x && abs((int)spaceship_average[i].position.y - (int)spaceship_average[j].position.y) <= 150 * (int)scale_y;

			if (collision_box_average)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship_average[j].position.x - spaceship_average[i].position.x, spaceship_average[j].position.y - spaceship[i].position.y };
				const float length_between_spaceships = (float)sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / length_between_spaceships, collision_vector.y / length_between_spaceships };
				const float scalar_product_1 = spaceship_average[i].direction.x * collision_normal.x + spaceship_average[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship_average[j].direction.x * collision_normal.x + spaceship_average[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship_average[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship_average[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship_average[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship_average[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship_average[i].direction = rebound_vector_1;
				spaceship_average[i].position.x += .01f * collision_vector.x;
				spaceship_average[i].position.y += .01f * collision_vector.y;
				collision_box_average = 0;
				break;
			}
		}
		for (int j = 0; j < 20; j++) // gros contre petit
		{
			if (j / 4 != i)
				collision_box_small = abs((int)spaceship_average[i].position.x - (int)spaceship_small[j].position.x) <= 100 * (int)scale_x && abs((int)spaceship_average[i].position.y - (int)spaceship_small[j].position.y) <= 100 * (int)scale_y;

			if (collision_box_small)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship_small[j].position.x - spaceship_average[i].position.x, spaceship_small[j].position.y - spaceship_average[i].position.y };
				const float length_between_spaceships = (float)sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / length_between_spaceships, collision_vector.y / length_between_spaceships };
				const float scalar_product_1 = spaceship_average[i].direction.x * collision_normal.x + spaceship_average[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship_small[j].direction.x * collision_normal.x + spaceship_small[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship_small[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship_small[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship_average[i].direction = rebound_vector_1;
				spaceship_small[j].direction = rebound_vector_2;
				spaceship_small[i].position.x += .01f * collision_vector.x;
				spaceship_small[i].position.y += .01f * collision_vector.y;
				collision_box_small = 0;
				break;
			}
		}
	}

	for (int i = 0; i < 20; i++)
	{
		
		for (int j = 0; j < 20; j++) // gros contre petit
		{
			if (j / 4 != i)
				collision_box_small = abs((int)spaceship_small[i].position.x - (int)spaceship_small[j].position.x) <= 100 * (int)scale_x && abs((int)spaceship_small[i].position.y - (int)spaceship_small[j].position.y) <= 100 * (int)scale_y;

			if (collision_box_small)
			{
				//calcul du vecteur rebond
				const sfVector2f collision_vector = { spaceship_small[j].position.x - spaceship_small[i].position.x, spaceship_small[j].position.y - spaceship_small[i].position.y };
				const float length_between_spaceships = (float)sqrt(pow(collision_vector.x, 2) + pow(collision_vector.y, 2));
				const sfVector2f collision_normal = { collision_vector.x / length_between_spaceships, collision_vector.y / length_between_spaceships };
				const float scalar_product_1 = spaceship_small[i].direction.x * collision_normal.x + spaceship_small[i].direction.y * collision_normal.y;
				const float scalar_product_2 = spaceship_small[j].direction.x * collision_normal.x + spaceship_small[j].direction.y * collision_normal.y;
				const sfVector2f rebound_vector_1 = { spaceship_small[i].direction.x - 2 * scalar_product_1 * collision_normal.x, spaceship_small[i].direction.y - 2 * scalar_product_1 * collision_normal.y };
				const sfVector2f rebound_vector_2 = { spaceship_small[j].direction.x - 2 * scalar_product_2 * collision_normal.x, spaceship_small[j].direction.y - 2 * scalar_product_2 * collision_normal.y };
				// donne la bonne direction au bond vaisseau
				spaceship_small[i].direction = rebound_vector_1;
				spaceship_small[i].position.x += .01f * collision_vector.x;
				spaceship_small[i].position.y += .01f * collision_vector.y;
				collision_box_small = 0;
				break;
			}
		}
	}

}

void destroy_spaceship(void) // detruit les vaisseaux quand le jeu est ferme
{
	for(int i = 0; i<20; i++)
	{
		if(spaceship_small[i].sprite)
			sfSprite_destroy(spaceship_small[i].sprite);
		if(spaceship_small[i].texture)
			sfTexture_destroy(spaceship_small[i].texture);
	}
	for (int i = 0; i < 10; i++)
	{
		if(spaceship_average[i].sprite)
			sfSprite_destroy(spaceship_average[i].sprite);
		if(spaceship_average[i].texture)
			sfTexture_destroy(spaceship_average[i].texture);
	}
	for (int i = 0; i < 5; i++)
	{
		if(spaceship[i].sprite)
			sfSprite_destroy(spaceship[i].sprite);
		if(spaceship[i].texture)
			sfTexture_destroy(spaceship[i].texture);
	}
}

void reset_pos_spaceship(void) // reset la position de tous les vaisseaux
{

	for (int i = 0; i < 5; i++)
	{
		get_random_pos();
		spaceship[i].position = (sfVector2f){ (float)zone_x[zone], (float)zone_y[zone] };
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
	}
	for (int i = 0; i < 10; i++)
	{
		if (spaceship[i / 2].little)
		{
			get_random_pos();
			spaceship_average[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
			sfSprite_setPosition(spaceship_average[i].sprite, spaceship_average[i].position);
		}
		else
		{
			spaceship_average[i].previous_position = spaceship_average[i].position;
			sfSprite_setPosition(spaceship_average[i].sprite, spaceship_average[i].position);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (spaceship_average[i / 2].little)
		{
			get_random_pos();
			spaceship_small[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
			sfSprite_setPosition(spaceship_small[i].sprite, spaceship_small[i].position);
		}
		else
		{
			spaceship_small[i].position = spaceship_average[i / 2].position;
			sfSprite_setPosition(spaceship_small[i].sprite, spaceship_small[i].position);
		}
	}
}

int created = 0;
int destroyed = 0;
int spaceship_destroyed = 0;
int min_to_display_spaceship = 0;
void spawn_spaceship(sfRenderWindow* window) { // spawn les vaisseaux
	if(spaceship_destroyed >= 20)
	{
		next_level();
	}
	if (created == 0)
	{
		created = 1;
		destroy_spaceship(); // detruit les vaisseaux s'il y en a deja de cree
		create_spaceship(); // creer des nouveaux vaisseaux
	}
	for (int j = 0; j < 20; j++)
	{
		if (spaceship_average[j / 2].little) // si le vaisseau de taille superieur a ete detruit
		{
			if (!spaceship_small[j].little) // et si le vaisseau n'a pas ete detruit
			{
				spaceship_small[j].position.x += spaceship_small[j].direction.x * spaceship_small[j].speed * return_dt(); // donne un mouvement dans une direction aleatoire au vaisseau
				spaceship_small[j].position.y += spaceship_small[j].direction.y * spaceship_small[j].speed * return_dt();

				if(spaceship_small[j].speed <= spaceship_small[j].speed_max) // augmente la vitesse jusqu'a ce qu'il atteigne sa vitesse max
				{
					spaceship_small[j].speed *= 1.001f;
				}

				if (spaceship_small[j].position.x > (1920 + 120) * scale_x) // wrap around
				{
					spaceship_small[j].position.x = (-120) * scale_x;
				}
				if (spaceship_small[j].position.x < (-120) * scale_x)
				{
					spaceship_small[j].position.x = (1920 + 120) * scale_x;
				}

				if (spaceship_small[j].position.y > (1080 + 120) * scale_y)
				{
					spaceship_small[j].position.y = (-120) * scale_y;
				}
				if (spaceship_small[j].position.y < (-120) * scale_y)
				{
					spaceship_small[j].position.y = (1080 + 120) * scale_y;
				}
				sfSprite_setPosition(spaceship_small[j].sprite, spaceship_small[j].position); // actualise sur la window
			}
		}
		else // si le vaisseau de taille superieur n'a pas ete detruit
		{
			spaceship_small[j].position = spaceship_average[j / 2].position; // met la position du vaisseau a celle du vaisseau superieur
			sfSprite_setPosition(spaceship_small[j].sprite, spaceship_average[j / 2].position);
		}
		if (!spaceship_small[j].little) // si le vaisseau n'a pas ete detruit
		{
			sfRenderWindow_drawSprite(window, spaceship_small[j].sprite, NULL); // affiche le vaisseau
		}
		if (collision(window, j, 0) || (is_exploded() && spaceship_average[j / 2].little)) // si le vaisseau a ete touche
		{
			spaceship_small[j].position = (sfVector2f){ INFINITY, INFINITY }; // detruit le vaisseau
			spaceship_small[j].little = 1;
			spaceship_destroyed++;
		}
	}
	for (int j = 0; j < 10; j++)
	{
		if (spaceship[j / 2].little)
		{
			if (!spaceship_average[j].little)
			{
				spaceship_average[j].position.x += spaceship_average[j].direction.x * spaceship_average[j].speed * return_dt();
				spaceship_average[j].position.y += spaceship_average[j].direction.y * spaceship_average[j].speed * return_dt();

				if (spaceship_average[j].speed <= spaceship_average[j].speed_max)
				{
					spaceship_average[j].speed *= 1.001f;
				}

				if (spaceship_average[j].position.x > (1920 + 120) * scale_x)
				{
					spaceship_average[j].position.x = (-120) * scale_x;
				}
				if (spaceship_average[j].position.x < (-120) * scale_x)
				{
					spaceship_average[j].position.x = (1920 + 120) * scale_x;
				}

				if (spaceship_average[j].position.y > (1080 + 120) * scale_y)
				{
					spaceship_average[j].position.y = (-120) * scale_y;
				}
				if (spaceship_average[j].position.y < (-120) * scale_y)
				{
					spaceship_average[j].position.y = (1080 + 120) * scale_y;
				}
				sfSprite_setPosition(spaceship_average[j].sprite, spaceship_average[j].position);
			}
		}
		else
		{
			spaceship_average[j].position = spaceship[j / 2].position;
			sfSprite_setPosition(spaceship_average[j].sprite, spaceship_average[j].position);
		}
		if (!spaceship_average[j].little)
		{
			sfRenderWindow_drawSprite(window, spaceship_average[j].sprite, NULL);
		}
		if (collision(window, j, 1) || (is_exploded() && spaceship[j / 2].little))
		{
			spaceship_average[j].position = (sfVector2f){ INFINITY, INFINITY };
			spaceship_average[j].little = 1;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		
		if (!spaceship[i].little)
		{
			spaceship[i].position.x += spaceship[i].direction.x * spaceship[i].speed * return_dt();
			spaceship[i].position.y += spaceship[i].direction.y * spaceship[i].speed * return_dt();

			if (spaceship[i].speed <= spaceship[i].speed_max)
			{
				spaceship[i].speed *= 1.001f;
			}

			if (spaceship[i].position.x > (1920 + 120) * scale_x)
			{
				spaceship[i].position.x = (-120) * scale_x;
			}
			if (spaceship[i].position.x < (-120) * scale_x)
			{
				spaceship[i].position.x = (1920 + 120) * scale_x;
			}

			if (spaceship[i].position.y > (1080 + 120) * scale_y)
			{
				spaceship[i].position.y = (-120) * scale_y;
			}
			if (spaceship[i].position.y <( -120) * scale_y)
			{
				spaceship[i].position.y = (1080 + 120) * scale_y;
			}
			sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
			if (!spaceship[i].little)
			{
				sfRenderWindow_drawSprite(window, spaceship[i].sprite, NULL);
			}
			if (collision(window, i, 2) || is_exploded())
			{
				spaceship[i].position = (sfVector2f){ INFINITY, INFINITY };
				spaceship[i].little = 1;
			}
		}
	}
}

int collision_spaceship(void) // detecte la collision avec l'asteroid
{
	int collided_spaceship = 0;

	int collision_box_big = 0;
	int collision_box_average = 0;
	int collision_box_small = 0;
	// si une collision entre l'asteroide et n'importe quel vaisseau est detecte
	for (int i = 0; i < 20; i++)
	{
		collision_box_small = abs((int)asteroid.position.x - (int)spaceship_small[i].position.x) <= 70 * (int)scale_x && abs((int)asteroid.position.y - (int)spaceship_small[i].position.y) <= 70 * (int)scale_y;
		if (collision_box_small)
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		collision_box_average = abs((int)asteroid.position.x - (int)spaceship_average[i].position.x) <= 95 * (int)scale_x && abs((int)asteroid.position.y - (int)spaceship_average[i].position.y) <= 95 * (int)scale_y;
		if (collision_box_average)
			break;
	}
	for (int i = 0; i < 5; i++)
	{
		collision_box_big = abs((int)asteroid.position.x - (int)spaceship[i].position.x) <= 130 * (int)scale_x && abs((int)asteroid.position.y - (int)spaceship[i].position.y) <= 130 * (int)scale_y;
		if (collision_box_big)
			break;
	}
	if (collision_box_big || collision_box_average || collision_box_small)
	{
		collided_spaceship = 1;
	}
	return collided_spaceship;
}

void reset_spaceship(void) // reset les spaceships quand la partie est recommence
{
	for(int i = 0; i<4; i++)
	{
		zone_x[i] = 0 ;
		zone_y[i] = 0 ;

		
	}
	for (int i = 0; i < 5; i++)
	{
		if (is_leveling())
		{
			spaceship[i].speed += (2.0f/17) * scale_x;
			spaceship[i].speed_max = spaceship[i].speed * 2;
		}
		spaceship_exploded[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		if (is_leveling())
		{
			spaceship_average[i].speed += (2.0f / 17) * scale_x;
			spaceship_average[i].speed_max = spaceship[i].speed * 2;
		}
		spaceship_exploded_average[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		if (is_leveling())
		{
			spaceship_small[i].speed += (2.0f / 17) * scale_x;
			spaceship_small[i].speed_max = spaceship[i].speed * 2;
		}
		spaceship_exploded_little[i] = 0;
	}
	created = 0;
	destroyed = 0;
	min_to_display_spaceship = 0;
	spaceship_destroyed = 0;
}

void set_difficulty(const int diff) // met la difficulte a la difficulte choisi
{
	difficulty = diff;
}