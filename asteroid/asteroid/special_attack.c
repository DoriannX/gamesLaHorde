
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "special_attack.h"

#include <stdio.h>

#include "character.h"
#include "print.h"
#include "scale.h"

int exploded = 0;
int animate = 0;
float alpha_special_attack = 255;
sfRectangleShape* animation_rectangle = NULL;



void animation(sfRenderWindow* window) // fait une petite animation quand la capacite speciale est utilise
{
	if (!animation_rectangle)
	{
		animation_rectangle = sfRectangleShape_create();
		sfRectangleShape_setOrigin(animation_rectangle, (sfVector2f) { (1920.0f / 2)* scale_x, (1080.0f / 2)* scale_y });
		sfRectangleShape_setPosition(animation_rectangle, (sfVector2f) { (1920.0f / 2)* scale_x, (1080.0f / 2)* scale_y });
		sfRectangleShape_setSize(animation_rectangle, (sfVector2f) {( 1920.0f)* scale_x, (1080.0f) * scale_y});
		sfRectangleShape_setFillColor(animation_rectangle, sfWhite);
	}
	if(alpha_special_attack > 0)
	{
		const sfColor animation_color = { 255, 255, 255, (sfUint8)alpha_special_attack };
		sfRectangleShape_setFillColor(animation_rectangle, animation_color); // fait apparaitre un ecran blanc qui va disparaitre progressivement
		alpha_special_attack -= 5.0f;
	}
	else
	{
		alpha_special_attack = 255;
	}
	sfRenderWindow_drawRectangleShape(window, animation_rectangle, NULL);

}
int first_entry = 1;
void explode(sfRenderWindow* window) // attaque special
{
	if(explode_time)
	{
		if (sfKeyboard_isKeyPressed(sfKeyLShift) && sfTime_asSeconds(sfClock_getElapsedTime(explode_time)) >= 60) { // pouvoir se reset toutes les 60 secondes
			animate = 1;
			alpha_special_attack = 255;
			sfClock_restart(explode_time);
			exploded = 1; // divise tous les vaisseaux aux alentours
		}
		else
		{
			exploded = 0;
		}
	}else if(first_entry)
	{
		if (sfKeyboard_isKeyPressed(sfKeyLShift) && first_entry) { // le temps de recharge se lance la premiere fois que le joueur appuie
			set_tuto(2, 0);
			explode_time = sfClock_create();
			first_entry = 0;
			animate = 1;
			alpha_special_attack = 255;
			sfClock_restart(explode_time);
			exploded = 1; // divise tous les vaisseaux aux alentours
		}
		else
		{
			exploded = 0;
		}
	}
	if(animate)
	{
		if(alpha_special_attack > 0)
		{
			animation(window);
		}else
		{
			animate = 0;
		}
	}

}

int is_exploded(void)
{
	return exploded;
	
}

void destroy_animation(void)
{
	sfRectangleShape_destroy(animation_rectangle);
}

int is_animating(void)
{
	return animate;
}

void reset_special_attack(void)
{
	exploded = 0;
	animate = 0;
	alpha_special_attack = 255;
	animation_rectangle = NULL;
	explode_time = NULL;
	first_entry = 1;
}