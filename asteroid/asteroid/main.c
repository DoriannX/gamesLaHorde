
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "dt.h"
#include "arial.h"
#include "gameOver.h"
#include "menu_start.h"
#include "print.h"
#include "score_manager.h"
#include "shoot.h"
#include "spaceship.h"
#include "special_attack.h"
#include "UI.h"
sfVideoMode screen_size;
sfVideoMode mode;
// creation des variables

sfRenderWindow* window;

void init(void) { // initialise les variables
	srand(time(NULL));
	screen_size = sfVideoMode_getDesktopMode();

	asteroid.sprite = sfSprite_create();
	asteroid.texture = sfTexture_createFromFile("sprites/spriteAsteroid.png", NULL);
	asteroid.sprite_size = (sfVector2f){ 1024, 1024 };
	asteroid.origin = (sfVector2f){ asteroid.sprite_size.x / 2, asteroid.sprite_size.y / 2 };
	asteroid.position.x = (float)screen_size.width * ((int)1920 / 2) / 1920; asteroid.position.y = (float)screen_size.height * ((int)1080 / 2) / 1080;
	create_sprite(asteroid.sprite, asteroid.texture, asteroid.origin, asteroid.scale, -90, asteroid.position);

	beginning = sfClock_create();
	arial = sfFont_createFromFile("arial.ttf");
	beginning = sfClock_create();
	time_between_shoot = sfClock_create();
	life_time_shoot = sfClock_create();


	mode.width = screen_size.width; // donne a la fenetre la taille de l'ecran
	mode.height = screen_size.height;
	mode.bitsPerPixel = 32;
	window = sfRenderWindow_create(mode, "Asteroid", sfClose, NULL); // creer une window
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
			update_life(); // actualise les vies
			shoot(window); // permet au joueur de tirer
			move_character(&asteroid, window); // deplace le personnage
			spawn_spaceship(window); // fait apparaitre des vaisseau 
			explode(window); // permet au joueur d'utiliser son attaque spe
			display_uis(window);
		}
		sfRenderWindow_display(window);
	}

	destroy();

	return 0;
}