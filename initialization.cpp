#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"structs.h"
#include"initialization.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 1280, win_height = 720;

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init()
{
	//SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Promblem with initialization: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
	{
		printf("Couldn't init SDL_Image! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
	if (res & IMG_INIT_PNG) printf("Initialized PNG libary.\n"); else printf("Couldn't init PNG libary.\n");
	if (res & IMG_INIT_PNG) printf("Initialized JPG libary.\n"); else printf("Couldn't init JPG libary.\n");

	if (TTF_Init())
	{
		printf("Couldn't init SDL_TTF! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("Just Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("win: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}


	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Window couldn`t create: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}

