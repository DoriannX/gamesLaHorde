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
int logo_displayed = 1;
int title_displayed = 0;
int selection_displayed = 0;
int option_displayed = 0;
sfSprite* logo_sprite = NULL;
sfTexture* logo_texture = NULL;
sfSprite* title_sprite = NULL;
sfTexture* title_texture = NULL;
sfRectangleShape* start_button = NULL;
sfRectangleShape* option_button = NULL;
sfRectangleShape* quit_button = NULL;
float alpha_logo = 255;
float alpha_title = 0;
sfFont* alien = NULL;
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
		create_sprite(title_sprite, title_texture, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 }, (sfVector2f) { 1.0f, 1.0f }, 0, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 });
	}
	if(logo_displayed)
	{
		const sfColor logo_color = { 255, 255, 255, (sfUint8)alpha_logo };
		if (alpha_logo > 0)
		{
			alpha_logo -= 1.0f;
		}
		if (alpha_logo <= 0 || event.type == sfEvtMouseButtonReleased || sfKeyboard_isKeyPressed(sfKeySpace))
		{
			logo_displayed = 0;
			title_displayed = 1;
			alpha_logo = 255;
		}
		sfSprite_setColor(logo_sprite, logo_color);
		sfRenderWindow_drawSprite(window, logo_sprite, NULL);
	}

	if(title_displayed)
	{
		const sfColor title_color = { 255, 255, 255, (sfUint8)alpha_title };
		sfSprite_setColor(title_sprite, title_color);
		sfRenderWindow_drawSprite(window, title_sprite, NULL);
		alien = (alien) ? alien : sfFont_createFromFile("fonts/alien.ttf");
		print_str("sdioretsa", 200, (sfVector2f) { 1920.0f / 2,1080- 200 }, sfWhite, window, alien);
		if (alpha_title < 255)
		{
			alpha_title += 1.0f;
		}else
		{
			selection_displayed = 1;
			title_displayed = 0;
			title_texture = NULL;
		}
	}

	if(selection_displayed)
	{
		title_texture = (title_texture) ? title_texture : sfTexture_createFromFile("sprites/background_option_menu.png", NULL);
		sfSprite_setTexture(title_sprite, title_texture, 0);
		start_button = (start_button) ? start_button : sfRectangleShape_create();
		option_button = (option_button) ? option_button : sfRectangleShape_create();
		quit_button = (quit_button) ? quit_button : sfRectangleShape_create();
		sfRectangleShape* list_button[] = { start_button, option_button, quit_button };
		for(int i = 0; i<3; i++)
		{
			sfRectangleShape_setFillColor(list_button[i], (sfColor) { 255, 255, 255, 100 });
			sfRectangleShape_setOrigin(list_button[i], (sfVector2f) { sfRectangleShape_getSize(start_button).x / 2, sfRectangleShape_getSize(start_button).y / 2 });
			sfRectangleShape_setPosition(list_button[i], (sfVector2f) { 1920.0f / 2, 1080.0f / 2 - 150 + 150.0f*(float)i });
			sfRectangleShape_setScale(list_button[i], (sfVector2f) { 1.0f, 1.0f });
			sfRectangleShape_setSize(list_button[i], (sfVector2f) { 420, 100 });
		}
		sfRenderWindow_drawSprite(window, title_sprite, NULL);

		if((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f/2+210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2-150 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2-150 - 50)
		{
			sfRenderWindow_drawRectangleShape(window, start_button, NULL);
			if(sfMouse_isButtonPressed(sfMouseLeft))
			{
				selection_displayed = 0;
				menu_displayed = 0;
			}
		}
		if ((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f / 2 + 210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2- 50)
		{
			sfRenderWindow_drawRectangleShape(window, option_button, NULL);
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				selection_displayed = 0;
			}
		}
		if ((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f / 2 + 210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2 + 150 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2 + 150 - 50)
		{
			sfRenderWindow_drawRectangleShape(window, quit_button, NULL);
			if (sfMouse_isButtonPressed(sfMouseLeft))
			{
				sfRenderWindow_close(window);
			}
		}

		print_str("start", 70, sfRectangleShape_getPosition(start_button), sfBlack, window, alien);
		print_str("option", 70, sfRectangleShape_getPosition(option_button), sfBlack, window, alien);
		print_str("quit", 70, sfRectangleShape_getPosition(quit_button), sfBlack, window, alien);
	}
}

void destroy_menu(void)
{
	sfSprite_destroy(logo_sprite);
	sfTexture_destroy(logo_texture);
	sfSprite_destroy(title_sprite);
	sfTexture_destroy(title_texture);
	sfFont_destroy(alien);
}