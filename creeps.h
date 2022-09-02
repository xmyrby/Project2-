#pragma once
#include<iostream>
#include"structs.h"

void initCreepTextures(const char filename[], Creep* creeps);

void DestructCreeps(int i, Creep* creeps);

void setCreep(int& max_count_creeps, Creep* creeps);

void SetWayCreeps(int& x);

void ClickCreep(int i, int mouse_x, int mouse_y, bool& mousebtdown, Creep* creeps);

void HealthCreep(int i, Creep* creeps);

void AnimationCreeps(int& curpos, int i,Creep* creeps);

void DrawCreeps(int& curpos, int mouse_x, int mouse_y, bool& mousebtdown, int& max_count_creeps, Creep* creeps);