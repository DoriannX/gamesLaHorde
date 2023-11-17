#include <stdio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

#include "character.h"
#include "scale.h"

sfSprite* map_sprite = NULL;
sfTexture* map_texture = NULL;

void display_map(sfRenderWindow* window) // affiche la map en arriere plan
{
	if(!map_sprite)
	{
		map_sprite = sfSprite_create();
		map_texture = sfTexture_createFromFile("sprites/star_background.png", NULL);
		create_sprite(map_sprite, map_texture, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 }, (sfVector2f) { 1.0f * scale_x, 1.0f * scale_y }, 0, (sfVector2f) { (1920.0f / 2)* scale_x, (1080.0f / 2)* scale_y });
	}
	sfRenderWindow_drawSprite(window, map_sprite, 0);
}

void destroy_map(void) // detruit la map quand tout est terminé
{
	sfSprite_destroy(map_sprite);
	sfTexture_destroy(map_texture);
}