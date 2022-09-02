#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


void DeInit(int error);

void Init();

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Rect* rect);

void initBackgroundsTextures(const char filename[]);

void ChangedBackground();