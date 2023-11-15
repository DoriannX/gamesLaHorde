
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "spaceship.h"

#include <math.h>

#include "character.h"
#include "dt.h"
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
void create_spaceship(void) // creer un vaisseau
{
	zone_x[0] = get_random_number(-120, 1920 + 120); // lui donne une position random en dehors de ce que le joueur peut voir
	zone_x[1] = get_random_number(1920, 1920 + 120);
	zone_x[2] = get_random_number(-120, 1920 + 120);
	zone_x[3] = get_random_number(-120, 0);

	zone_y[0] = get_random_number(-120, 0);
	zone_y[1] = get_random_number(-120, 1080 + 120);
	zone_y[2] = get_random_number(1080, 1080 + 120);
	zone_y[3] = get_random_number(-120, 1080 + 120);

	const int zone = get_random_number(0, 4);

	for (int i = 0; i < 5; i++)
	{
		spaceship[i].origin = (sfVector2f){ 1, 1 }; // creer un gros vaisseau
		spaceship[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
		spaceship[i].previous_position = spaceship[i].position;
		spaceship[i].scale = (sfVector2f){ .2f, .2f };
		spaceship[i].speed = (float)2 / 17;
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
		spaceship_average[i].scale = (sfVector2f){ .1f, .1f };
		spaceship_average[i].speed = (float)4 / 17;
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
		spaceship_small[i].scale = (sfVector2f){ .05f, .05f };
		spaceship_small[i].speed = (float)6 / 17;
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
	zone_x[0] = get_random_number(-120, 1920 + 120);
	zone_x[1] = get_random_number(1920, 1920 + 120);
	zone_x[2] = get_random_number(-120, 1920 + 120);
	zone_x[3] = get_random_number(-120, 0);

	zone_y[0] = get_random_number(-120, 0);
	zone_y[1] = get_random_number(-120, 1080 + 120);
	zone_y[2] = get_random_number(1080, 1080 + 120);
	zone_y[3] = get_random_number(-120, 1080 + 120);

	const int zone = get_random_number(0, 4);

	for (int i = 0; i < 5; i++)
	{
		spaceship[i].position = (sfVector2f){ (int)zone_x[zone], (int)zone_y[zone] };
		sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
	}
	for (int i = 0; i < 10; i++)
	{
		if (spaceship[i / 2].little)
		{
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
int min_to_display_spaceship = 0;
void spawn_spaceship(sfRenderWindow* window) { // spawn les vaisseaux
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

				if (spaceship_small[j].position.x > 1920 + 120) // wrap around
				{
					spaceship_small[j].position.x = -120;
				}
				if (spaceship_small[j].position.x < -120)
				{
					spaceship_small[j].position.x = 1920 + 120;
				}

				if (spaceship_small[j].position.y > 1080 + 120)
				{
					spaceship_small[j].position.y = -120;
				}
				if (spaceship_small[j].position.y < -120)
				{
					spaceship_small[j].position.y = 1080 + 120;
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
		if (collision(window, j, "small") || (is_exploded() && spaceship_average[j / 2].little)) // si le vaisseau a ete touche
		{
			spaceship_small[j].position = (sfVector2f){ INFINITY, INFINITY }; // detruit le vaisseau
			spaceship_small[j].little = 1;
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

				if (spaceship_average[j].position.x > 1920 + 120)
				{
					spaceship_average[j].position.x = -120;
				}
				if (spaceship_average[j].position.x < -120)
				{
					spaceship_average[j].position.x = 1920 + 120;
				}

				if (spaceship_average[j].position.y > 1080 + 120)
				{
					spaceship_average[j].position.y = -120;
				}
				if (spaceship_average[j].position.y < -120)
				{
					spaceship_average[j].position.y = 1080 + 120;
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
		if (collision(window, j, "average") || (is_exploded() && spaceship[j / 2].little))
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

			if (spaceship[i].position.x > 1920 + 120)
			{
				spaceship[i].position.x = -120;
			}
			if (spaceship[i].position.x < -120)
			{
				spaceship[i].position.x = 1920 + 120;
			}

			if (spaceship[i].position.y > 1080 + 120)
			{
				spaceship[i].position.y = -120;
			}
			if (spaceship[i].position.y < -120)
			{
				spaceship[i].position.y = 1080 + 120;
			}
			sfSprite_setPosition(spaceship[i].sprite, spaceship[i].position);
			if (!spaceship[i].little)
			{
				sfRenderWindow_drawSprite(window, spaceship[i].sprite, NULL);
			}
			if (collision(window, i, "big") || is_exploded())
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
		collision_box_small = abs((int)asteroid.position.x - (int)spaceship_small[i].position.x) <= 70 && abs((int)asteroid.position.y - (int)spaceship_small[i].position.y) <= 70;
		if (collision_box_small)
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		collision_box_average = abs((int)asteroid.position.x - (int)spaceship_average[i].position.x) <= 95 && abs((int)asteroid.position.y - (int)spaceship_average[i].position.y) <= 95;
		if (collision_box_average)
			break;
	}
	for (int i = 0; i < 5; i++)
	{
		collision_box_big = abs((int)asteroid.position.x - (int)spaceship[i].position.x) <= 130 && abs((int)asteroid.position.y - (int)spaceship[i].position.y) <= 130;
		if (collision_box_big)
			break;
	}
	if (collision_box_big || collision_box_average || collision_box_small)
	{
		collided_spaceship = 1;
	}
	return collided_spaceship;
}

void reset_spaceship(void)
{
	for(int i = 0; i<4; i++)
	{
		zone_x[i] = 0 ;
		zone_y[i] = 0 ;
	}
	for (int i = 0; i < 5; i++)
	{
		spaceship_exploded[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		spaceship_exploded_average[i] = 0;
	}
	for (int i = 0; i < 20; i++)
	{
		spaceship_exploded_little[i] = 0;
	}
	created = 0;
	destroyed = 0;
	min_to_display_spaceship = 0;
}