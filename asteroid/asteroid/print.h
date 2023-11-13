#ifndef PRINT_H
#define PRINT_H
#include <SFML/Graphics.h>

void print_str(const char* chr, const int size, const sfVector2f position, const sfColor color, sfRenderWindow* window);
void print_int(const int number, const int size, const sfVector2f position, const sfColor color, sfRenderWindow* window);
void print_float(const float number, const int size, const sfVector2f position, sfRenderWindow* window);
#endif