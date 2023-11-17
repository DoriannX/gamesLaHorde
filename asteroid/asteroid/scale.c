#include "scale.h"

#include <SFML/Window/VideoMode.h>

void init_scale(void) // rescale tous les objets, uis, textes, menus etc a la bonne taille en fonction de l'ecran
{
	size_screen = sfVideoMode_getDesktopMode();
	scale_x = (float)size_screen.width/ 1920;
	scale_y = (float)size_screen.height / 1080;
}
