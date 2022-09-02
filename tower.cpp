#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include"structs.h"
#include"background.h"
#include"globalvar.h"

#pragma region TOWER

//Tower towers[4];
Places place;
Shop shop[3];
Shopbg shopbg;

bool buy = false;
int buyType = 0;

int num = 0;

void initShopbgTextures()
{
	shopbg.tex = loadTextureFromFile("shopbg.png", &shopbg.anim);
	shopbg.anim = { 406,236,150,34 };
	shopbg.spawn = { 0,500,1280,220 };
}

void initShopTextures(Tower* towers)
{
	for (int i = 0; i < 3; i++)
	{
		shop[i].tex = loadTextureFromFile("Tower.png", &towers[i].anim);
	}
}

void SetShop()
{
	shop[0].anim = { 0,0,150,105 };
	shop[0].spawn = { 100,550,100,100 };

	shop[1].anim = { 175,0,150,105 };
	shop[1].spawn = { 300,550,100,100 };

	shop[2].anim = { 355,0,150,105 };
	shop[2].spawn = { 500,550,100,100 };
}

void DrawShop()
{
	SDL_RenderCopy(ren, shopbg.tex, &shopbg.anim, &shopbg.spawn);
	SetShop();
	for (int i = 0; i < 3; i++)
	{
		SDL_RenderCopy(ren, shop[i].tex, &shop[i].anim, &shop[i].spawn);
	}
}

void initTowerTextures(const char filename[], Tower* towers)
{
	for (int i = 0; i < 4; i++)
	{
		towers[i].tex = loadTextureFromFile(filename, &towers[i].anim);
	}
}

void initBulletTextures(const char filename[], Tower* towers)
{
	for (int i = 0; i < 4; i++)
	{
		towers[i].shot_tex = loadTextureFromFile(filename, &towers[i].shot_anim);
	}
}

int Distance(Creep creep, Tower tower)
{
	return sqrt((creep.xWay - tower.spawn.x) * (creep.xWay - tower.spawn.x) + (creep.yWay - tower.spawn.y) * (creep.yWay - tower.spawn.y));
}

//Отрисовка пули если она активна, если нет то она пропадает за задником
void WayBullet(Creep& creep, Tower& tower)
{
	float angle = atan2(creep.yWay - tower.spawn.y, creep.xWay - tower.spawn.x);
	tower.bullet.x += cos(angle);
	tower.bullet.y += sin(angle);
	if (Distance(creep, tower) >= tower.dist)
	{
		//Отнимаем хп у крипа
		tower.bullet.x = (tower.spawn.x + tower.spawn.w / 2);
		tower.bullet.y = (tower.spawn.y + tower.spawn.h / 2);
	}
	//Отрисовываем
}

void CheckDistance(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers)
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < max_count_creeps; i++)
		{
			if (creeps[i].active)
			{
				towers[k].dist = Distance(creeps[i], towers[k]);
				//printf("%i", towers[k].dist);
				//system("cls");
				if (towers[k].dist <= towers[k].rad and towers[k].lock == 101)
				{
					towers[k].lock = i;
					timerBullet++;
					WayBullet(creeps[towers[k].lock], towers[k]);

				}
			}
		}
	}
}

void setTypeTower(int buyType, int& countTower, Tower* towers)
{
	if (buyType == 1)
	{
		towers[countTower].anim = { 0,0,150,105 };

		towers[countTower].rad = 200;
		towers[countTower].lock = 101;

		//Индекс башни для сохранения
		towers[countTower].index = towers[countTower].index + 1;

		//Параметры пули
		towers[countTower].bullet.x = towers[countTower].spawn.x + towers[countTower].spawn.w / 2;
		towers[countTower].bullet.y = towers[countTower].spawn.y + towers[countTower].spawn.h / 2;
		towers[countTower].bullet.w = 20;
		towers[countTower].bullet.h = 20;
		towers[countTower].shot_spawn = true;

		buyType = 0;
		countTower++;
	}
	else if (buyType == 2)
	{
		towers[countTower].anim = { 175,0,150,105 };

		towers[countTower].rad = 200;
		towers[countTower].lock = 101;

		towers[countTower].index = towers[countTower].index + 2;

		towers[countTower].bullet.x = towers[countTower].spawn.x + towers[countTower].spawn.w / 2;
		towers[countTower].bullet.y = towers[countTower].spawn.y + towers[countTower].spawn.h / 2;
		towers[countTower].bullet.w = 20;
		towers[countTower].bullet.h = 20;
		towers[countTower].shot_spawn = true;

		buyType = 0;
		countTower++;
	}
	else if (buyType == 3)
	{
		towers[countTower].anim = { 355,0,150,105 };

		towers[countTower].rad = 200;
		towers[countTower].lock = 101;

		towers[countTower].index = towers[countTower].index + 3;

		towers[countTower].bullet.x = towers[countTower].spawn.x + towers[countTower].spawn.w / 2;
		towers[countTower].bullet.y = towers[countTower].spawn.y + towers[countTower].spawn.h / 2;
		towers[countTower].bullet.w = 20;
		towers[countTower].bullet.h = 20;
		towers[countTower].shot_spawn = true;

		buyType = 0;
		countTower++;
	}

}

//Определение места постройки башни
void buildTower(int mouse_x, int mouse_y, int& countTower, bool& mousebtdown, bool& checkSpawn1, bool& checkSpawn2, bool& checkSpawn3, bool& checkSpawn4, Tower* towers, bool& load)
{
	if (buy == true)
	{

		//Левая башня сверху
		if (checkSpawn1 == false and mousebtdown == true and mouse_x >= place.p1.x and mouse_x <= place.p1.x + place.p1.w and mouse_y >= place.p1.y and mouse_y <= place.p1.y + place.p1.h)
		{
			checkSpawn1 = true;

			mousebtdown = false;
			buy = false;

			towers[countTower].spawn = { 340,183,150,105 };

			towers[countTower].index = 10;

			setTypeTower(buyType, countTower, towers);
		}

		//Правая башня сверху
		else if (checkSpawn2 == false and mousebtdown == true and mouse_x >= place.p2.x and mouse_x <= place.p2.x + place.p2.w and mouse_y >= place.p2.y and mouse_y <= place.p2.y + place.p2.h)
		{
			checkSpawn2 = true;

			mousebtdown = false;
			buy = false;

			towers[countTower].spawn = { 923,180,150,105 };

			towers[countTower].index = 20;

			setTypeTower(buyType, countTower, towers);
		}

		else if (checkSpawn3 == false and mousebtdown == true and mouse_x >= place.p3.x and mouse_x <= place.p3.x + place.p3.w and mouse_y >= place.p3.y and mouse_y <= place.p3.y + place.p3.h)
		{
			checkSpawn3 = true;

			mousebtdown = false;
			buy = false;

			towers[countTower].spawn = { 128,363,150,105 };

			towers[countTower].index = 30;

			setTypeTower(buyType, countTower, towers);
		}

		else if (checkSpawn4 == false and mousebtdown == true and mouse_x >= place.p4.x and mouse_x <= place.p4.x + place.p4.w and mouse_y >= place.p4.y and mouse_y <= place.p4.y + place.p4.h)
		{
			checkSpawn4 = true;

			mousebtdown = false;
			buy = false;

			towers[countTower].spawn = { 594,363,150,105 };

			towers[countTower].index = 40;

			setTypeTower(buyType, countTower, towers);
		}

		//Отмена покупки башни(не работает)
		//if (rightbtdown == true)
		//{
		//	buyType = 0;
		//	rightbtdown = false;
		//	buy = false;
		//}
	}

	if (load)
	{
		int placeT = 0;
		int typeT = 0;
		for (int i = 0; i < 4; i++)
		{
			placeT = towers[i].index / 10;//место для башни целое от 10
			typeT = towers[i].index % 10;//тип башни остаток от 10
			switch (placeT)
			{
			case 1:
			{
				towers[i].spawn = { 340,183,150,105 };
				checkSpawn1 = true;
				break;
			}
			case 2:
			{
				towers[i].spawn = { 923,180,150,105 };
				checkSpawn2 = true;
				break;
			}
			case 3:
			{
				towers[i].spawn = { 128,363,150,105 };
				checkSpawn3 = true;
				break;
			}
			case 4:
			{
				towers[i].spawn = { 594,363,150,105 };
				checkSpawn4 = true;
				break;
			}
			break;
			}

			switch (typeT)
			{
			case 1:
			{
				buyType = 1;
				break;
			}
			case 2:
			{
				buyType = 2;
				break;
			}
			case 3:
			{
				buyType = 3;
				break;
			}
			break;
			}
			setTypeTower(buyType, i, towers);
		}
		load = false;
	}

}

void buyingClickTower(int mouse_x, int mouse_y, bool& mousebtdown)
{
	if (mousebtdown == true and mouse_x >= shop[0].spawn.x and mouse_x <= shop[0].spawn.x + shop[0].spawn.w and mouse_y >= shop[0].spawn.y and mouse_y <= shop[0].spawn.y + shop[0].spawn.h)
	{
		buy = true;
		buyType = 1;

		mousebtdown = false;
	}
	else
		if (mousebtdown == true and mouse_x >= shop[1].spawn.x and mouse_x <= shop[1].spawn.x + shop[1].spawn.w and mouse_y >= shop[1].spawn.y and mouse_y <= shop[1].spawn.y + shop[1].spawn.h)
		{
			buy = true;
			buyType = 2;

			mousebtdown = false;
		}
		else
			if (mousebtdown == true and mouse_x >= shop[2].spawn.x and mouse_x <= shop[2].spawn.x + shop[2].spawn.w and mouse_y >= shop[2].spawn.y and mouse_y <= shop[2].spawn.y + shop[2].spawn.h)
			{
				buy = true;
				buyType = 3;

				mousebtdown = false;
			}
}

//Чек на занятое место
void DrawTower(int mouse_x, int mouse_y, int& countTower, bool& mousebtdown, bool& checkSpawn1, bool& checkSpawn2, bool& checkSpawn3, bool& checkSpawn4, Tower* towers, bool& load, int timerBullet, int max_count_creeps, Creep* creeps)
{
	for (int i = 0; i < 4; i++)
	{
		DrawShop();
		buyingClickTower(mouse_x, mouse_y, mousebtdown);
		buildTower(mouse_x, mouse_y, countTower, mousebtdown, checkSpawn1, checkSpawn2, checkSpawn3, checkSpawn4, towers, load);
		CheckDistance(timerBullet, max_count_creeps, creeps, towers);
		//Где(поверхность) | Что(Текстура) | Размер чего-то(NULL если не кусочек) | Где появиться что-то(NULL вся поверхность)
		SDL_RenderCopy(ren, towers[i].tex, &towers[i].anim, &towers[i].spawn);
	}
}
#pragma endregion