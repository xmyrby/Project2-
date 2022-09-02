#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "background.h"
#include"structs.h"
#include"initialization.h"
#include"globalvar.h"

#pragma region BACKGROUND

Background backgrounds;

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("Couldn't load image %s! Error: %s", filename, SDL_GetError());
		system("pause");
		DeInit(1);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	int img_width = surface->w;
	int img_height = surface->h;
	*rect = { NULL,NULL,img_width,img_height };
	SDL_FreeSurface(surface);
	return texture;
}

void initBackgroundsTextures(const char filename[])
{
	backgrounds.tex = loadTextureFromFile(filename, &backgrounds.rect);
}

void ChangedBackground()
{
	SDL_RenderCopy(ren, backgrounds.tex, &backgrounds.rect, NULL);
}
#pragma endregion
