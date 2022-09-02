#include <iostream>

#include<SDL.h>
#include <SDL_ttf.h>
#include<SDL_image.h>

#include "Initialization.h"
#include"Structs.h"
#include"GlobalVar.h"
#include"background.h"
#include"Menu.h"

#pragma region MENU

Menu menu[3];

int red = 0;
int green = 0;
int blue = 0;

Texture loadFont(const char text[], const char fontname[], SDL_Color color, int hgt)
{
	TTF_Font* font = TTF_OpenFont(fontname, hgt);
	if (!font)
	{
		printf("\nCouldn't load font %s! Error: %s\n", fontname, SDL_GetError());
		system("pause");
		DeInit(1);
	}

	SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
	if (!surf)
	{
		printf("\nCouldn't load surface from TTF_RenderText_Blended! Error: %s\n", SDL_GetError());
		system("pause");
		DeInit(1);
	}


	Texture texture;
	texture.tex = SDL_CreateTextureFromSurface(ren, surf);
	texture.dstrect = { 0, 0, surf->w, surf->h };;

	texture.w = surf->w;
	texture.h = surf->h;

	TTF_CloseFont(font);
	SDL_FreeSurface(surf);

	return texture;
}

void MenuDestroy()
{
	for (int i = 0; i < 3; i++)
	{
		SDL_DestroyTexture(menu[i].textures.tex);
	}
}

void MenuClick(int mouse_x, int mouse_y, bool& startgame, bool& startapp, bool& bgcreeps, bool& mousebtdown,bool& isRunning)
{
	for (int i=0;i<3;i++)
	{
		if (mousebtdown)
		{
			if (mouse_x >= menu[i].drawRect.x and mouse_x <= menu[i].drawRect.x + menu[i].drawRect.w and mouse_y >= menu[i].drawRect.y and mouse_y <= menu[i].drawRect.y + menu[i].drawRect.h)
			{
				if (i == 0)
				{
					startapp = false;

					startgame = true;

					bgcreeps = true;

					mousebtdown = false;
					printf("CLICK ON START");
				}
				if (i == 2)
				{
					isRunning = false;
				}
			}
		}
	}

}

void drawMenu(int i, int mouse_x, int mouse_y, bool& startgame, bool& startapp, bool& bgcreeps, bool& mousebtdown)
{
	ChangedBackground();
	char options[][10] = { "Start","Options","Exit" };

	for (int i = 0, y = 200; i < 3; i++, y += 100)
	{
		menu[i].textures = loadFont(options[i], "fonts\\Chava-Regular.ttf", { 0,0,180,255 }, 25);
		//Меняет цвет если мышка в зоне кнопки
		if (mouse_x >= menu[i].drawRect.x and mouse_x <= menu[i].drawRect.x + menu[i].drawRect.w and mouse_y >= menu[i].drawRect.y and mouse_y <= menu[i].drawRect.y + menu[i].drawRect.h)
		{
			MenuDestroy();
			menu[i].textures = loadFont(options[i], "fonts\\Chava-Regular.ttf", { 180,0,0,255 }, 25);
		}
		menu[i].drawRect.y = y;
		menu[i].drawRect.w = menu[i].textures.dstrect.w;
		menu[i].drawRect.h = menu[i].textures.dstrect.h;
		menu[i].drawRect.x = (1280 - menu[i].drawRect.w) / 2;
		menu[i].textures.dstrect = menu[i].drawRect;
		SDL_RenderCopy(ren, menu[i].textures.tex, NULL, &menu[i].textures.dstrect);
	}
	
}
#pragma endregion
