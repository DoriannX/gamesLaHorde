#pragma once
#ifndef SPECIAL_ATTACK_H
#define SPECIAL_ATTACK_H

void explode(sfRenderWindow* window);
sfClock* explode_time;
void explode_reset(void);
void destroy_animation(void);
int is_exploded(void);
int is_animating(void);
#endif
