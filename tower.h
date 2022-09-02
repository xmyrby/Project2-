#pragma once
#include<iostream>
#include"structs.h"

void initShopbgTextures();

void initShopTextures(Tower* towers);

void SetShop();

void DrawShop();

void initTowerTextures(const char filename[], Tower* towers);

void initBulletTextures(const char filename[], Tower* towers);

void WayBullet(Creep* creeps, Tower* towers);

int Distance(Creep* creeps, Tower* towers, int k, int i);

void CheckDistance(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers);

void setTypeTower(int buyType, int& countTower, Tower* towers);

void buildTower(int mouse_x, int mouse_y, int& countTower, bool& mousebtdown, bool& checkSpawn1, bool& checkSpawn2, bool& checkSpawn3, bool& checkSpawn4, Tower* towers);

void buyingClickTower(int mouse_x, int mouse_y, bool& mousebtdown);

void Shop();

void DrawTower(int mouse_x, int mouse_y, int& countTower, bool& mousebtdown, bool& checkSpawn1, bool& checkSpawn2, bool& checkSpawn3, bool& checkSpawn4, Tower* towers, bool& load, int timerBullet, int max_count_creeps, Creep* creeps);