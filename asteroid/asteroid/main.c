#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "dt.h"
#include "arial.h"
#include "shoot.h"
#include "spaceship.h"
sfVideoMode screenSize;
sfVideoMode mode;
// creation des variables
character asteroid = {
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
sfRenderWindow* window;

void init(void) { // initialise les variables

	srand((unsigned int)time(0));
	screenSize = sfVideoMode_getDesktopMode();

	asteroid.sprite = sfSprite_create();
	asteroid.texture = sfTexture_createFromFile("sprites/spriteAsteroid.png", NULL);
	asteroid.sprite_size = (sfVector2f){ 1024, 1024 };
	asteroid.origin = (sfVector2f){ asteroid.sprite_size.x / 2, asteroid.sprite_size.y / 2 };
	asteroid.position.x = (float)screenSize.width * ((int)1920 / 2) / 1920; asteroid.position.y = (float)screenSize.height * ((int)1080 / 2) / 1080;
	create_sprite(asteroid.sprite, asteroid.texture, asteroid.origin, asteroid.scale, -90, asteroid.position);

	arial = sfFont_createFromFile("arial.ttf");
	beginning = sfClock_create();
	time_between_shoot = sfClock_create();
	life_time_shoot = sfClock_create();

}

void destroy(void) {
	sfSprite_destroy(asteroid.sprite);
	sfTexture_destroy(asteroid.texture);
	sfRenderWindow_destroy(window);
	sfClock_destroy(time_between_shoot);
	sfClock_destroy(life_time_shoot);
}

int main(void) {
	beginning = sfClock_create();
	init();
	mode.width = screenSize.width;
	mode.height = screenSize.height;
	mode.bitsPerPixel = 32;
	window = sfRenderWindow_create(mode, "Asteroid", sfFullscreen, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	while (sfRenderWindow_isOpen(window)) {
		sfEvent event;
		if (!sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}

		sfRenderWindow_clear(window, sfBlack);
		delta_time();
		if (!collision_spaceship())
		{
			shoot(window);
			move_character(&asteroid, window);
			spawn_spaceship(window);
		}
		sfRenderWindow_display(window);
	}

	destroy();

	return 0;
}