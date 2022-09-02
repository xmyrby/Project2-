#include<iostream>
#include"structs.h"

void initBulletTextures(const char filename[]);

//void WayBullet(int max_count_creeps, Creep* creeps,Tower* towers);

//void SpawnPlace(int i, int& timerBullet, Tower* towers);

//void AreaIntersection(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers);

void WayBullet(Creep* creeps, Tower* towers);

void SpawnPlace(Tower* towers);

int Distance(Tower* towers, Creep* creeps, int k, int i);

void CheckDistance(int& timerBullet, int max_count_creeps, Creep* creeps, Tower* towers);