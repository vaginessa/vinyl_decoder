#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "surface.h"
#include "point.h"

SDL_Surface* load_surface(SDL_Surface* screen_surface, const char* path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL) {
		printf("Unable to load image %s: %s\n", path, IMG_GetError());
		goto out;
	}

	//Convert surface to screen format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, screen_surface->format, 0);
	if (optimizedSurface == NULL) {
		printf("Unable to optimize image %s: %s\n", path, SDL_GetError());
	}

out:
	return optimizedSurface;
}


void put_red_pixel(SDL_Surface *surface, const struct point *pt)
{
	Uint32* pixels = (Uint32*)surface->pixels;
	pixels += pt->y * surface->w + pt->x;
	*pixels = SDL_MapRGB(surface->format, 255, 0, 0);  
}

struct pixel get_pixel(SDL_Surface *surface, const struct point *pt)
{
	struct pixel pix;

	Uint32* pixels = (Uint32*)surface->pixels;
	pixels += pt->y * surface->w + pt->x;
	Uint8* pixel_bytes = (Uint8*) pixels;

	pix.r = pixel_bytes[0];
	pix.g = pixel_bytes[1];
	pix.b = pixel_bytes[2];
	return pix;
}
