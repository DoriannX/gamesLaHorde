#pragma once
#ifndef MENU_START_H
#define MENU_START_H
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>

int is_menu_displayed(void);
void display_menu(sfRenderWindow* window);
void display_menu(sfRenderWindow* window, const sfEvent event);

#endif