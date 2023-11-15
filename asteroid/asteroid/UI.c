#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include "UI.h"

#include "character.h"
#include "dt.h"
#include "print.h"
#include "score_manager.h"
#include "special_attack.h"

sfSprite* heart_sprite = NULL;
sfSprite* cooldown_ability = NULL;
sfTexture* heart_texture = NULL;
sfTexture* heart_texture_death = NULL;
sfTexture* cooldown_ability_texture = NULL;

void display_uis(sfRenderWindow* window)
{
	print_str("score : ", 24, (sfVector2f) { 1920.0f / 2 - 280, 1080 - 50 }, sfWhite, window, NULL);
	print_int(return_score(), 24, (sfVector2f) { 1920.0f/2 - 200, 1080 - 45 }, sfWhite, window);
	if(!heart_sprite)
	{
		heart_sprite = sfSprite_create();
		heart_texture = sfTexture_createFromFile("sprites/heart.png", NULL);
		heart_texture_death = sfTexture_createFromFile("sprites/death.png", NULL);
		create_sprite(heart_sprite, heart_texture, (sfVector2f) { 1024.0f / 2, 1024.0f / 2 }, (sfVector2f) { .05f, .05f }, 0, (sfVector2f) { 1920.0f / 2 + 200, 1080 - 50 });
	}
	for(int i = 0; i < asteroid.vie; i++) // affiche les coeurs
	{
		sfSprite_setTexture(heart_sprite, heart_texture, 0);
		sfSprite_setPosition(heart_sprite, (sfVector2f) { 1920.0f / 2 + 200 + 50.0f*(float)(i), 1080 - 50 });
		sfRenderWindow_drawSprite(window, heart_sprite, NULL);

	}
	for (int i = 0; i < 3-asteroid.vie; i++) // affiche les coeurs vides
	{
		sfSprite_setTexture(heart_sprite, heart_texture_death, 0);
		sfSprite_setPosition(heart_sprite, (sfVector2f) { 1920.0f / 2 + 200 + 50.0f * 2 - 50 * (float)(i), 1080 - 50 });
		sfRenderWindow_drawSprite(window, heart_sprite, NULL);

	}
	if(!cooldown_ability)
	{
		cooldown_ability = sfSprite_create();
		cooldown_ability_texture = sfTexture_createFromFile("sprites/cooldown_ability.png", NULL);
		create_sprite(cooldown_ability, cooldown_ability_texture, (sfVector2f) { 1024.0f / 2, 1024.0f / 2 }, (sfVector2f) { .05f, .05f }, 0, (sfVector2f) { 1920.0f / 2 - 350, 50 });
	}
	sfRenderWindow_drawSprite(window, cooldown_ability, 0);
	if(is_animating()) // affiche l'icone de capacite speciale et l'anime quand le joueur l'utilise
	{
		const sfVector2f direction_vector = (sfVector2f){ (sfSprite_getPosition(cooldown_ability).x) + .2f * (1920.0f / 2 - sfSprite_getPosition(cooldown_ability).x),   (sfSprite_getPosition(cooldown_ability).y) + .2f * (1080.0f / 2 - sfSprite_getPosition(cooldown_ability).y) };
		const sfVector2f size = (sfVector2f){ sfSprite_getScale(cooldown_ability).x * 1.2f, sfSprite_getScale(cooldown_ability).y * 1.2f };
		if (size.x < .3f)
		{
			sfSprite_setScale(cooldown_ability, size);
		}
		sfSprite_setPosition(cooldown_ability,direction_vector);
	}else
	{
		const sfVector2f direction_vector = (sfVector2f){ (sfSprite_getPosition(cooldown_ability).x) + .2f * ((sfVector2f) { 1920.0f / 2 - 350, 50 }.x - sfSprite_getPosition(cooldown_ability).x),   (sfSprite_getPosition(cooldown_ability).y) + .2f * ((sfVector2f) { 1920.0f / 2 - 350, 50 }.y - sfSprite_getPosition(cooldown_ability).y) };
		const sfVector2f size = (sfVector2f){ sfSprite_getScale(cooldown_ability).x * .8f, sfSprite_getScale(cooldown_ability).y * .8f };
		if (size.x > .05f)
		{
			sfSprite_setScale(cooldown_ability, size);
		}
		sfSprite_setPosition(cooldown_ability, direction_vector);
	}
	float recharge_time = 0;
	if(explode_time)
	{
		recharge_time = 60 - sfTime_asSeconds(sfClock_getElapsedTime(explode_time));
	}
	print_int((int)recharge_time, 20, (sfVector2f) { 1920.0f / 2 - 280, 50 }, sfWhite, window); // affiche le temps restant avant de pouvoir reutiliser la capacite spe
}

void destroy_uis(void)
{
	sfSprite_destroy(heart_sprite);
	sfTexture_destroy(heart_texture);
	sfTexture_destroy(heart_texture_death);
	sfSprite_destroy(cooldown_ability);
	sfTexture_destroy(cooldown_ability_texture);
}

void reset_uis(void)
{
	heart_sprite = NULL;
	cooldown_ability = NULL;
	heart_texture = NULL;
	heart_texture_death = NULL;
	cooldown_ability_texture = NULL;
}
