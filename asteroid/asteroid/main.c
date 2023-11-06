#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    sfVideoMode mode = { 800, 600, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "CSFML Test", sfResize | sfClose, NULL);

    sfCircleShape* shape = sfCircleShape_create();
    sfCircleShape_setRadius(shape, 100);
    sfCircleShape_setFillColor(shape, sfGreen);
    sfCircleShape_setPosition(shape, (sfVector2f) { 350, 250 });

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawCircleShape(window, shape, NULL);
        sfRenderWindow_display(window);
    }

    sfCircleShape_destroy(shape);
    sfRenderWindow_destroy(window);

    return 0;
}