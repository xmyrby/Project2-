#include<iostream>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include"initialization.h"
#include"globalvar.h"
#include"background.h"
#include"creeps.h"
#include"tower.h"
#include"structs.h"

int countBullet = 0;

Shot shot[100];

int dist = 0;

int k = 0;

void initBulletTextures(const char filename[])
{
	for (int i = 0; i < 100; i++)
	{
		shot[i].tex = loadTextureFromFile(filename, &shot[i].anim);
	}
}

//ќтрисовка пули если она активна, если нет то она пропадает за задником
void WayBullet( Creep* creeps, Tower* towers)
{
	for (int i = 0; i < 4; i++)
	{
		if (shot[i].spawn)
		{
			k = towers[i].lock;
			if (shot[i].bullet.y != creeps[k].yWay)
			{
				if (shot[i].bullet.y > creeps[k].yWay)
				{
					shot[i].bullet.y = shot[i].bullet.y - 1;
				}
				else if (shot[i].bullet.y < creeps[k].yWay)
				{
					shot[i].bullet.y = shot[i].bullet.y + 1;
				}
			}
			if (shot[i].bullet.x != creeps[k].xWay)
			{
				if (shot[i].bullet.x > creeps[k].xWay)
				{
					shot[i].bullet.x = shot[i].bullet.x - 1;
				}
				else if (shot[i].bullet.x < creeps[k].xWay)
				{
					shot[i].bullet.x = shot[i].bullet.x + 1;
				}
			}
			if (shot[i].bullet.x >= creeps[k].xWay and shot[i].bullet.x <= creeps[k].xWay + 42 and shot[i].bullet.y >= creeps[k].yWay and shot[i].bullet.y <= creeps[k].yWay + 84)
			{
				shot[i].spawn = false;
				creeps[k].health = creeps[k].health - 25;
			}
			else if (creeps[k].active == false )
			{
				towers[i].lock = 101;
				shot[i].spawn = false;
			}
			SDL_RenderCopy(ren, shot[i].tex, &shot[i].anim, &shot[i].bullet);
		}
	}
}

//¬ыбор места спавна пули
void SpawnPlace(Tower* towers)
{
	for (int i = 0; i < 4; i++)
	{
		if (shot[i].spawn == false)
		{
			shot[i].bullet.x = towers[i].spawn.x + towers[i].spawn.w / 2;
			shot[i].bullet.y = towers[i].spawn.y + towers[i].spawn.h / 2;
			shot[i].bullet.w = 20;
			shot[i].bullet.h = 20;
			shot[i].spawn = true;
		}
	}


	////ќбнуление кол-во пуль(перезапуск)
	//if (countBullet >= 100)
	//{
	//	countBullet = 0;
	//}
	//else if (timerBullet % 100 == 0)
	//{
	//	shot[countBullet].bullet.x = towers[i].spawn.x + towers[i].spawn.w / 2;
	//	shot[countBullet].bullet.y = towers[i].spawn.y + towers[i].spawn.h / 2;
	//	shot[countBullet].bullet.w = 20;
	//	shot[countBullet].bullet.h = 20;
	//	shot[countBullet].spawn = true;
	//	countBullet++;
	//}
}

int Distance(Tower* towers, Creep* creeps, int k, int i)
{
	return sqrt((creeps[i].xWay - towers[k].spawn.x + towers[k].spawn.w / 2) * (creeps[i].xWay - towers[k].spawn.x + towers[k].spawn.w / 2) + (creeps[i].yWay - towers[k].spawn.y + towers[k].spawn.h / 2) * (creeps[i].yWay - towers[k].spawn.y + towers[k].spawn.h / 2));
}

//void AreaIntersection(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers)
//{
//	for (int k = 0; k < 4; k++)
//	{
//		for (int i = 0; i < max_count_creeps; i++)
//		{
//
//			////÷ель в области
//			if (creeps[i].heart.x >= towers[k].range.x and creeps[i].heart.x <= towers[k].range.x + towers[k].range.w and creeps[i].heart.y >= towers[k].range.y and creeps[i].heart.y <= towers[k].range.y + towers[k].range.h)
//			{
//				if (creeps[i].active)
//				{
//					if (towers[k].priority == 0)
//					{
//						towers[k].priority = i;
//					}
//					SpawnPlace(k, timerBullet towers);
//					timerBullet++;
//					WayBullet(max_count_creeps, creeps, towers);
//				}
//			}
//			//≈сли крип за зоной или умер, то приоритет башни обнул€етс€
//			else if (creeps[i].heart.x <= towers[k].range.x or creeps[i].heart.x >= towers[k].range.x + towers[k].range.w or creeps[i].heart.y <= towers[k].range.y or creeps[i].heart.y >= towers[k].range.y + towers[k].range.h or creeps[i].active == false)
//			{
//				towers[k].priority = 0;
//			}
//		}
//	}
//}

void CheckDistance(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers)
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < max_count_creeps; i++)
		{
			if (creeps[i].active)
			{
				dist = Distance(towers, creeps, k, i);
				if (dist <= towers[k].rad and towers[k].lock == 101)
				{
					towers[k].lock = i;

				}
				SpawnPlace(towers);
				timerBullet++;
				WayBullet(creeps, towers);
			}
		}
	}
}