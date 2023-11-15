#include "menu_start.h"

#include <corecrt_math.h>
#include <stdio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "dt.h"
#include "gameOver.h"
#include "print.h"
#include "score_manager.h"
#include "shoot.h"
#include "spaceship.h"
#include "special_attack.h"
#include "UI.h"
int menu_displayed = 1;
int logo_displayed = 1;
int title_displayed = 0;
int selection_displayed = 0;
int option_displayed = 0;
int last_menu = 0;
int is_paused = 0;
sfSprite* menu_sprite = NULL;
sfSprite* selection_arrow_sprite = NULL;
sfTexture* menu_texture = NULL;
sfTexture* selection_arrow_texture = NULL;
sfRectangleShape* start_button = NULL;
sfRectangleShape* option_button = NULL;
sfRectangleShape* quit_button = NULL;
float alpha_logo = 255;
float alpha_title = 0;
sfFont* alien = NULL;
int actual_click = 0;
int previous_click = 0;
int actual_escape = 0;
int previous_escape = 0;
float time_since_beginning = 0;
sfClock* clock_beginning = NULL;
int is_menu_displayed(void)
{
	return menu_displayed;
}

void display_menu(sfRenderWindow* window, const sfEvent event)
{
	actual_click = sfMouse_isButtonPressed(sfMouseLeft);
	actual_escape = sfKeyboard_isKeyPressed(sfKeyEscape);
	if(!menu_sprite)
	{
		menu_sprite = sfSprite_create();
		menu_texture = sfTexture_createFromFile("sprites/laHorde.png", NULL);
		create_sprite(menu_sprite, menu_texture, (sfVector2f) { 482.0f / 2, 486.0f / 2 }, (sfVector2f) { 1.0f, 1.0f }, 0, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 });
		selection_arrow_sprite = sfSprite_create();
		selection_arrow_texture = sfTexture_createFromFile("sprites/selection_arrow.png", NULL);
		create_sprite(selection_arrow_sprite, selection_arrow_texture, (sfVector2f) { 512.0f / 2, 512.0f / 2 }, (sfVector2f) { .1f, .1f }, 0, (sfVector2f) { 1920.0f / 2+250, 1080.0f / 2 - 320 + 150 });
	}
	if(logo_displayed)
	{
		const sfColor logo_color = { 255, 255, 255, (sfUint8)alpha_logo };
		if (alpha_logo > 0)
		{
			alpha_logo -= 5.0f;
		}
		if (alpha_logo <= 0 || actual_click && !previous_click)
		{
			previous_click = actual_click;
			logo_displayed = 0;
			title_displayed = 1;
			alpha_logo = 255;
			menu_texture = NULL;
		}
		sfSprite_setColor(menu_sprite, logo_color);
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);
	}
	if(title_displayed)
	{
		if (!menu_texture)
		{
			menu_sprite = sfSprite_create();
			menu_texture = sfTexture_createFromFile("sprites/titleScreen.png", NULL);
			create_sprite(menu_sprite, menu_texture, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 }, (sfVector2f) { 1.0f, 1.0f }, 0, (sfVector2f) { 1920.0f / 2, 1080.0f / 2 });
		}
		const sfColor title_color = { 255, 255, 255, (sfUint8)alpha_title };
		sfSprite_setColor(menu_sprite, title_color);
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);
		alien = (alien) ? alien : sfFont_createFromFile("fonts/alien.ttf");
		print_str("sdioretsa", 200, (sfVector2f) { 1920.0f / 2,1080- 200 }, title_color, window, alien);
		if (alpha_title < 255)
		{
			alpha_title += 2.0f;
			if(alpha_title > 255)
			{
				alpha_title = 255;
			}
		}
		if (alpha_title >= 255 ||  (actual_click && !previous_click))
		{
			previous_click = actual_click;
			alpha_title = 255;
			sfSprite_setColor(menu_sprite, (sfColor){ 255, 255, 255, (sfUint8)alpha_title });
			selection_displayed = 1;
			title_displayed = 0;
			menu_texture = NULL;
		}
	}
	if(selection_displayed)
	{
		menu_texture = (menu_texture) ? menu_texture : sfTexture_createFromFile("sprites/background_option_menu.png", NULL);
		sfSprite_setTexture(menu_sprite, menu_texture, 0);
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
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);

		if((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f/2+210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2-150 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2-150 - 50)
		{
			sfRenderWindow_drawRectangleShape(window, start_button, NULL);
			if(actual_click && !previous_click)
			{
				previous_click = actual_click;
				selection_displayed = 0;
				menu_displayed = 0;
				menu_texture = NULL;
				clock_beginning = sfClock_create();
			}
		}
		if ((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f / 2 + 210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2- 50)
		{
			sfRenderWindow_drawRectangleShape(window, option_button, NULL);
			if (actual_click && !previous_click)
			{
				previous_click = actual_click;
				option_displayed = 1;
				menu_texture = NULL;
				selection_displayed = 0;
				last_menu = 0;
			}
		}
		if ((float)sfMouse_getPositionRenderWindow(window).x < 1920.0f / 2 + 210 && (float)sfMouse_getPositionRenderWindow(window).x > 1920.0f / 2 - 210
			&& (float)sfMouse_getPositionRenderWindow(window).y < 1080.0f / 2 + 150 + 50 && (float)sfMouse_getPositionRenderWindow(window).y > 1080.0f / 2 + 150 - 50)
		{
			sfRenderWindow_drawRectangleShape(window, quit_button, NULL);
			if (actual_click && !previous_click)
			{
				previous_click = actual_click;
				sfRenderWindow_close(window);
			}
		}

		print_str("start", 70, sfRectangleShape_getPosition(start_button), sfBlack, window, alien);
		print_str("option", 70, sfRectangleShape_getPosition(option_button), sfBlack, window, alien);
		print_str("quit", 70, sfRectangleShape_getPosition(quit_button), sfBlack, window, alien);
	}

	if (!menu_displayed && is_paused && !option_displayed)
	{
		if (actual_escape && !previous_escape)
		{
			previous_escape = actual_escape;
			is_paused = 0;
			option_displayed = 0;
			menu_texture = NULL;
		}
		menu_texture = (menu_texture) ? menu_texture : sfTexture_createFromFile("sprites/pause_menu.png", NULL);
		sfSprite_setTexture(menu_sprite, menu_texture, 0);
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);

		const sfVector2f pos_btnp[] = { { 1920.0f / 2, 1080.0f / 2 - 75 },  { 1920.0f / 2, 1080.0f / 2 + 75} };
		print_str("option", 50, pos_btnp[0], sfWhite, window, alien);
		print_str("quit", 50, pos_btnp[1], sfWhite, window, alien);

		sfRectangleShape* diff = sfRectangleShape_create();
		sfRectangleShape_setFillColor(diff, (sfColor) { 255, 255, 255, 100 });
		sfRectangleShape_setOrigin(diff, (sfVector2f) { sfRectangleShape_getSize(start_button).x / 2, sfRectangleShape_getSize(start_button).y / 2 });
		sfRectangleShape_setScale(diff, (sfVector2f) { 1.0f, 1.0f });
		sfRectangleShape_setSize(diff, (sfVector2f) { 420, 100 });
		for(int i = 0; i<2; i++)
		{
			if ((float)sfMouse_getPositionRenderWindow(window).x < pos_btnp[i].x + 210 && (float)sfMouse_getPositionRenderWindow(window).x > pos_btnp[i].x - 210
				&& (float)sfMouse_getPositionRenderWindow(window).y < pos_btnp[i].y + 50 && (float)sfMouse_getPositionRenderWindow(window).y > pos_btnp[i].y - 50)
			{
				sfRectangleShape_setPosition(diff, pos_btnp[i]);
				sfRenderWindow_drawRectangleShape(window, diff, NULL);

				if (actual_click && !previous_click)
				{
					if(i==0)
					{
						last_menu = 1;
						option_displayed = 1;
						menu_texture = NULL;
					}else
					{
						sfRenderWindow_close(window);
					}
					previous_click = actual_click;
				}
			}
		}

	}
	else
	{
		if (actual_escape && !previous_escape)
		{
			previous_escape = actual_escape;
			is_paused = 1;
		}
	}

	if(option_displayed)
	{
		menu_texture = (menu_texture) ? menu_texture : sfTexture_createFromFile("sprites/option_menu.png", NULL);
		sfSprite_setTexture(menu_sprite, menu_texture, 0);
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);
		const sfVector2f pos_diff[] = { {1920.0f / 2, 1080.0f / 2 - 320 + 150}, {1920.0f / 2, 1080.0f / 2 - 320 + 300},  {1920.0f / 2, 1080.0f / 2 - 320 + 450},  {1920.0f / 2, 1080.0f / 2 - 320 + 600} };
		print_str("difficulte", 100, (sfVector2f) {1920.0f/2, 1080.0f/2-320}, sfWhite, window, alien);
		print_str("noob", 70, pos_diff[0], sfWhite, window, alien);
		print_str("balanced", 70, pos_diff[1], sfWhite, window, alien);
		print_str("pro", 70, pos_diff[2], sfWhite, window, alien);
		print_str("back", 50, pos_diff[3], sfWhite, window, alien);
		sfRectangleShape* diff = sfRectangleShape_create();
		sfRectangleShape_setFillColor(diff, (sfColor) { 255, 255, 255, 100 });
		sfRectangleShape_setOrigin(diff, (sfVector2f) { sfRectangleShape_getSize(start_button).x / 2, sfRectangleShape_getSize(start_button).y / 2 });
		sfRectangleShape_setScale(diff, (sfVector2f) { 1.0f, 1.0f });
		sfRectangleShape_setSize(diff, (sfVector2f) { 420, 100 });
		for(int i = 0; i<4; i++)
		{
			if ((float)sfMouse_getPositionRenderWindow(window).x < pos_diff[i].x + 210 && (float)sfMouse_getPositionRenderWindow(window).x > pos_diff[i].x - 210
				&& (float)sfMouse_getPositionRenderWindow(window).y < pos_diff[i].y + 50 && (float)sfMouse_getPositionRenderWindow(window).y > pos_diff[i].y - 50)
			{
				sfRectangleShape_setPosition(diff, pos_diff[i]);
				sfRenderWindow_drawRectangleShape(window, diff, NULL);

				if (actual_click && !previous_click)
				{
					previous_click = actual_click;
					if(i == 0)
					{
						sfSprite_setPosition(selection_arrow_sprite, (sfVector2f) { pos_diff[i].x + 250, pos_diff[i].y });
						set_difficulty(0);
						update_speed();
					}
					if(i == 1)
					{
						sfSprite_setPosition(selection_arrow_sprite, (sfVector2f) { pos_diff[i].x + 250, pos_diff[i].y });
						set_difficulty(1);
						update_speed();
					}
					if(i==2)
					{
						sfSprite_setPosition(selection_arrow_sprite, (sfVector2f) { pos_diff[i].x + 250, pos_diff[i].y });
						set_difficulty(2);
						update_speed();
					}
					if(i==3)
					{
						if(last_menu == 0)
						{
							option_displayed = 0;
							selection_displayed = 1;
							menu_texture = NULL;
						}else
						{
							option_displayed = 0;
							menu_texture = NULL;
						}
					}
				}
			}
			sfRenderWindow_drawSprite(window, selection_arrow_sprite, 0);
		}
	}


	if (is_game_over())
	{
		menu_texture = (menu_texture) ? menu_texture : sfTexture_createFromFile("sprites/game_over_menu.png", NULL);
		sfSprite_setTexture(menu_sprite, menu_texture, 0);
		sfRenderWindow_drawSprite(window, menu_sprite, NULL);
		print_int(return_score(), 40, (sfVector2f) { 1920.0f / 2-140, 1080.0f / 2-200 }, sfWhite, window);
		print_str("pts", 40, (sfVector2f) { 1920.0f / 2-80, 1080.0f / 2-195 }, sfWhite, window, NULL);

		time_since_beginning = (time_since_beginning == 0.0f) ? sfTime_asSeconds(sfClock_getElapsedTime(clock_beginning)) : time_since_beginning;

		print_int((int)time_since_beginning, 40, (sfVector2f) { 1920.0f / 2 + 100, 1080.0f / 2 - 200 }, sfWhite, window);
		print_str("secs", 40, (sfVector2f) { 1920.0f / 2 + 170, 1080.0f / 2 - 210 }, sfWhite, window, NULL);

		const sfVector2f pos_btn[] = {{1920.0f/2, 1080.0f/2}, {1920.0f / 2, 1080.0f / 2+150} };

		print_str("restart", 50, pos_btn[0], sfWhite, window, alien);
		print_str("quit", 50, pos_btn[1], sfWhite, window, alien);
		sfRectangleShape* diff = sfRectangleShape_create();
		sfRectangleShape_setFillColor(diff, (sfColor) { 255, 255, 255, 100 });
		sfRectangleShape_setOrigin(diff, (sfVector2f) { sfRectangleShape_getSize(start_button).x / 2, sfRectangleShape_getSize(start_button).y / 2 });
		sfRectangleShape_setScale(diff, (sfVector2f) { 1.0f, 1.0f });
		sfRectangleShape_setSize(diff, (sfVector2f) { 420, 100 });
		for (int i = 0; i < 2; i++)
		{
			if ((float)sfMouse_getPositionRenderWindow(window).x < pos_btn[i].x + 210 && (float)sfMouse_getPositionRenderWindow(window).x > pos_btn[i].x - 210
				&& (float)sfMouse_getPositionRenderWindow(window).y < pos_btn[i].y + 50 && (float)sfMouse_getPositionRenderWindow(window).y > pos_btn[i].y - 50)
			{
				sfRectangleShape_setPosition(diff, pos_btn[i]);
				sfRenderWindow_drawRectangleShape(window, diff, NULL);
				if (actual_click && !previous_click)
				{
					if(i==0)
					{
						reset_character();
						reset_dt();
						reset_game_over();
						reset_score();
						reset_shoot();
						reset_spaceship();
						reset_special_attack();
						reset_uis();
						sfClock_restart(clock_beginning);
					}
					if(i==1)
					{
						sfRenderWindow_close(window);
					}
					previous_click = actual_click;
				}
			}
		}
	}
	

	if(!actual_click && previous_click)
	{
		previous_click = 0;
	}
	if (!actual_escape && previous_escape)
	{
		previous_escape = 0;
	}
}

int is_started(void)
{
	return !menu_displayed;
}

int return_is_paused(void)
{
	return is_paused;
}

void destroy_menu(void)
{
	sfSprite_destroy(menu_sprite);
	sfSprite_destroy(selection_arrow_sprite);
	sfTexture_destroy(menu_texture);
	sfTexture_destroy(selection_arrow_texture);
	sfFont_destroy(alien);
	sfRectangleShape_destroy(start_button);
	sfRectangleShape_destroy(option_button);
	sfRectangleShape_destroy(quit_button);
	sfClock_destroy(clock_beginning);
}