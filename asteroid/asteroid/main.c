#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "print.h"
#include "dt.h"
#include "arial.h"
#include "shoot.h"
#define PI 3.141592 
sfVideoMode screenSize;
sfVideoMode mode;
// création des variables
character asteroide = {
    .vie = 3,
    .sprite = sfNone,
    .spriteSize = {0, 0},
    .texture = sfNone,
    .position = {1920 / 2, 1080 / 2},
    .previousPosition = {1920 / 2, 1080 / 2},
    .speed = 0,
    .speedMax = 1,
    .acceleration = .05f,
    .deceleration = .99f,
    .direction = {0, 0},
    .scale = {0.15f, 0.15f},
    .origin = {1, 1},
    .rotation = 0
};
sfRenderWindow* window;

void init() { // initialise les variables
    screenSize = sfVideoMode_getDesktopMode();

    asteroide.sprite = sfSprite_create();
    asteroide.texture = sfTexture_createFromFile("sprites/spriteAsteroide.png", NULL);
    asteroide.spriteSize = (sfVector2f){ 1024, 1024 };
    asteroide.origin = (sfVector2f){ asteroide.spriteSize.x / 2, asteroide.spriteSize.y / 2 };
    asteroide.position.x = screenSize.width * (1920 / 2) / 1920; asteroide.position.y = screenSize.height * (1080 / 2) / 1080;
    createSprite(asteroide.sprite, asteroide.texture,asteroide.origin, asteroide.scale, -90, asteroide.position);

    arial = sfFont_createFromFile("arial.ttf");
    beginning = sfClock_create();

    projectile.color = sfWhite;
    projectile.direction = asteroide.direction;
    projectile.bounds.x = 15;
    projectile.bounds.y = 5;
    projectile.position = asteroide.position;
    projectile.previousPosition = projectile.position;
    projectile.rectangle = sfRectangleShape_create();
    projectile.rotation = angle;
    projectile.speed = 50;

    sfRectangleShape_setFillColor(projectile.rectangle, sfWhite);
    sfRectangleShape_setRotation(projectile.rectangle, projectile.rotation);
    sfRectangleShape_setSize(projectile.rectangle, projectile.bounds);
    sfRectangleShape_setOrigin(projectile.rectangle, (sfVector2f) { projectile.bounds.x / 2, projectile.bounds.y / 2 });
    sfRectangleShape_setPosition(projectile.rectangle, projectile.position);
}

void destroy() {
    sfSprite_destroy(asteroide.sprite);
    sfTexture_destroy(asteroide.texture);
    sfRenderWindow_destroy(window);
    sfRectangleShape_destroy(projectile.rectangle);
}

int main() {
    sfClock* beginning = sfClock_create();
    init();
    mode.width = screenSize.width;
    mode.height = screenSize.height;
    mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(mode, "CSFML Test", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        if (!sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);
        deltaTime();
        moveCharacter(&asteroide, window);
        shoot(window);
        sfRenderWindow_display(window);
    }

    destroy();

    return 0;
}