
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "arial.h"
void print_str(const char* chr, const int size, const sfVector2f position, const sfColor color, sfRenderWindow* window) { // affiche un str sur la window
	sfText* text = sfText_create(); // creer un texte pour stocker notre str a afficher
	sfText_setString(text, chr);//transforme le str en text
	sfText_setFont(text, arial); // lui donne une police
	sfText_setColor(text, color);//lui donne la taille
	sfText_setCharacterSize(text, size);// lui donne la position
	sfText_setPosition(text, position); // lui donne la position
	sfText_setOrigin(text, (sfVector2f) { sfText_getLocalBounds(text).width / 2.0f, sfText_getLocalBounds(text).height });// met l'origine au centre du texte
	sfRenderWindow_drawText(window, text, NULL);// affiche le texte

	sfText_destroy(text);
}

void print_int(const int number, const int size, const sfVector2f position, const sfColor color, sfRenderWindow* window) {// affiche un int dans la window
	sfText* integer = sfText_create();
	char str[12];
	snprintf(str, 12, "%d", number);// convertie un int en str
	sfText_setString(integer, str);
	sfText_setFont(integer, arial);
	sfText_setCharacterSize(integer, size);
	sfText_setPosition(integer, position);
	sfText_setColor(integer, color);
	sfText_setOrigin(integer, (sfVector2f) { sfText_getLocalBounds(integer).width / 2.0f, sfText_getLocalBounds(integer).height });
	sfRenderWindow_drawText(window, integer, NULL);

	sfText_destroy(integer);
}

void print_float(const float number, const int size, const sfVector2f position, sfRenderWindow* window) {// affiche un float dans la window
	sfText* floater = sfText_create();
	char str[12];
	snprintf(str, 12, "%f", number);// convertie un float en str

	sfText_setString(floater, str);
	sfText_setFont(floater, arial);
	sfText_setCharacterSize(floater, size);
	sfText_setPosition(floater, position);
	sfText_setOrigin(floater, (sfVector2f) { sfText_getLocalBounds(floater).width / 2.0f, sfText_getLocalBounds(floater).height });
	sfRenderWindow_drawText(window, floater, NULL);
	sfText_destroy(floater);
}