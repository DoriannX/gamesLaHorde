#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "character.h"
#include "dt.h"
#include "arial.h"
#include "gameOver.h"
#include "map.h"
#include "menu_start.h"
#include "scale.h"
#include "shoot.h"
#include "spaceship.h"
#include "special_attack.h"
#include "UI.h"

sfVideoMode mode;
sfRenderWindow* window;

void init(void) { // initialise les variables

	init_scale();
	srand(time(NULL));

	beginning = sfClock_create();
	arial = sfFont_createFromFile("arial.ttf");
	beginning = sfClock_create();
	time_between_shoot = sfClock_create();
	life_time_shoot = sfClock_create();


	mode.width = size_screen.width; // donne a la fenetre la taille de l'ecran
	mode.height = size_screen.height;
	mode.bitsPerPixel = 32;
	window = sfRenderWindow_create(mode, "Asteroid", sfFullscreen, NULL); // creer une window
	sfRenderWindow_setFramerateLimit(window, 60); // limite les fps a 60
}

void destroy(void) { // detruit tous les sprites, textures, clock etc
	sfSprite_destroy(asteroid.sprite);
	sfTexture_destroy(asteroid.texture);
	sfRenderWindow_destroy(window);
	sfClock_destroy(time_between_shoot);
	sfClock_destroy(life_time_shoot);
	sfFont_destroy(arial);
	sfClock_destroy(explode_time);
	sfClock_destroy(beginning);
	destroy_projectile();
	destroy_spaceship();
	destroy_animation();
	destroy_uis();
	destroy_map();
}

int main(void) { // main
	init(); // initialise toutes les variables
	while (sfRenderWindow_isOpen(window)) {
		sfEvent event;
		if (!sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

		sfRenderWindow_clear(window, sfBlack);
		delta_time(); // actualise le delta temps
		// on affiche le menu
		display_menu(window, event);
		if (!is_game_over() && is_started() && !return_is_paused()) // si la partie n'est pas perdu
		{
			display_map(window);
			update_life(); // actualise les vies
			shoot(window); // permet au joueur de tirer
			move_character(&asteroid, window); // deplace le personnage
			spawn_spaceship(window); // fait apparaitre des vaisseau 
			explode(window); // permet au joueur d'utiliser son attaque spe
			display_uis(window);
			tuto(window);
			collision_between_spaceships(window);
		}
		sfRenderWindow_display(window);
	}

	destroy();

	return 0;
}