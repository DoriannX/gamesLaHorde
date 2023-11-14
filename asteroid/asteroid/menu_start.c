#include "menu_start.h"

#include <stdio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "print.h"
int menu_displayed = 1;
int title_displayed = 0;
sfSprite* logo_sprite = NULL;
sfTexture* logo_texture = NULL;
sfSprite* title_sprite = NULL;
sfTexture* title_texture = NULL;
float alpha_logo = 255;
float alpha_title = 0;
int is_menu_displayed(void)
{
	return menu_displayed;
}

void display_menu(sfRenderWindow* window, const sfEvent event)
{
	if(!logo_sprite)
	{
		logo_sprite = sfSprite_create();
		logo_texture = sfTexture_createFromFile("sprites/laHorde.png", NULL);
		create_sprite(logo_sprite, logo_texture, (sfVector2f) { 482.0f / 2, 486.0f / 2 }, (sfVector2f) { 1.0f, 1.0f }, 0, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 });
	}
	if (!title_sprite)
	{
		title_sprite = sfSprite_create();
		title_texture = sfTexture_createFromFile("sprites/titleScreen.png", NULL);
		create_sprite(title_sprite, title_texture, (sfVector2f) { 960.0f / 2, 540.0f / 2 }, (sfVector2f) { 2.0f, 2.0f }, 0, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 });
	}
	const sfColor logo_color = { 255, 255, 255, (sfUint8)alpha_logo };
	const sfColor title_color = { 255, 255, 255, (sfUint8)alpha_title };
	if(alpha_logo > 0)
	{
		alpha_logo -= 1.0f;
	}
	if(alpha_logo <= 0 || event.type == sfEvtMouseButtonReleased || sfKeyboard_isKeyPressed(sfKeySpace))
	{
		title_displayed = 1;
		alpha_logo = 0;
	}
	sfSprite_setColor(logo_sprite, logo_color);
	sfRenderWindow_drawSprite(window, logo_sprite, NULL);

	if(title_displayed)
	{
		sfSprite_setColor(title_sprite, title_color);
		sfRenderWindow_drawSprite(window, title_sprite, NULL);
		print_str("sdioretsa", 200, (sfVector2f) { 1920.0f / 2,1080- 200 }, sfWhite, window);
		if (alpha_title < 255)
		{
			alpha_title += 1.0f;
		}
	}
}

void destroy_menu(void)
{
	sfSprite_destroy(logo_sprite);
	sfTexture_destroy(logo_texture);
	sfSprite_destroy(title_sprite);
	sfTexture_destroy(title_texture);
}