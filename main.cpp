#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include"structs.h"
#include "background.h"
#include"creeps.h"
#include"initialization.h"
#include"globalvar.h"
#include"tower.h"

#include"menu.h"

#include"save_and_load.h"


void Draw(int& curpos, int mouse_x, int mouse_y, bool& mousebtdown, int& countTower, bool& checkSpawn1, bool& checkSpawn2, bool& checkSpawn3, bool& checkSpawn4,int& max_count_creeps, int& timerBullet,Creep* creeps,Tower* towers,bool& load)
{
	ChangedBackground();
	DrawCreeps(curpos, mouse_x, mouse_y, mousebtdown, max_count_creeps,creeps);
	DrawTower(mouse_x, mouse_y, countTower, mousebtdown, checkSpawn1, checkSpawn2, checkSpawn3, checkSpawn4,towers,load,timerBullet,max_count_creeps,creeps);
	CheckDistance(timerBullet, max_count_creeps, creeps, towers);
	SDL_RenderPresent(ren);
	SDL_Delay(1000 / 60);
	curpos++;
}

int main(int argc, char* argv[])
{
	Init();
	srand(time(NULL));


	Creep creeps[25];
	Tower towers[4];

	initTowerTextures("Tower.png",towers);
	initCreepTextures("creepsbg.png",creeps);
	initShopbgTextures();
	initShopTextures(towers);
	initBulletTextures("cannonball.png",towers);

	int tt = 59;
	int mouse_x = 0, mouse_y = 0;
	int anpos = 0;

	int max_count_creeps = 0;

	bool mousebtdown = false;
	bool rightbtdown = false;

	bool isRunning = true;

	bool startgame = false;
	bool startapp = false;
	bool bgcreeps = false;
	bool bgmenu = false;

	int i = 0;

	int countTower = 0;

	bool checkSpawn4 = false;
	bool checkSpawn1 = false;
	bool checkSpawn2 = false;
	bool checkSpawn3 = false;

	int timerBullet = 0;

	bool load = false;

	SDL_Event ev;

	while (isRunning)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{

			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEMOTION:
			{
				mouse_x = ev.motion.x;
				mouse_y = ev.motion.y;
				//system("cls");
				//printf("X: %i\tY: %i", mouse_x, mouse_y);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_LEFT)
				{
					mouse_x = ev.button.x;
					mouse_y = ev.button.y;
					mousebtdown = true;

				}
				if (ev.button.button == SDL_BUTTON_RIGHT)
				{
					rightbtdown = true;
				}
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
				{
					startapp = false;
					break;
				}
				break;
				case SDL_SCANCODE_F1:
				{
					startapp = true;
					bgmenu = true;
					break;
				}
				case SDL_SCANCODE_F2:
				{
					startapp = false;
					break;
				}
				case SDL_SCANCODE_F3:
				{
					startgame = true;
					startapp = false;
					bgcreeps = true;
					break;
				}
				case SDL_SCANCODE_F4:
				{
					startgame = false;
					break;
				}
				case SDL_SCANCODE_F5:
				{
					SaveBin(towers);
					break;
				}
				case SDL_SCANCODE_F6:
				{
					LoadBin(towers);
					load = true;
					break;
				}
				
				}
			}
		}

		//menu
		if (startapp == true)//Включает меню
		{
			if (bgmenu == true)//Единожды загружает задник меню
			{
				initBackgroundsTextures("bgmenu.jpg");
				bgmenu = false;
			}
			drawMenu(i, mouse_x,  mouse_y, mousebtdown,  startapp, startgame,  bgcreeps);
			MenuClick(mouse_x, mouse_y, startgame, startapp, bgcreeps, mousebtdown,isRunning);
			MenuDestroy();
			SDL_RenderPresent(ren);
		}

		//game
		if (startgame == true)
		{
			startapp = false;//выключает меню

			if (bgcreeps == true)//Единожды загружает задник игры
			{
				initBackgroundsTextures("bg.jpg");
				bgcreeps = false;
			}

			tt++;//Задержка перед появленнием нового крипа
			if (tt % 60 == 0)
				setCreep(max_count_creeps,creeps);

			Draw(anpos, mouse_x, mouse_y, mousebtdown, countTower, checkSpawn1, checkSpawn2, checkSpawn3, checkSpawn4, max_count_creeps, timerBullet,creeps,towers,load);
		}

	}//isRunning

	TTF_CloseFont(0);

	DeInit(0);
	SDL_Quit();
	return 0;
}//main

