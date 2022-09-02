#pragma once
#include<iostream>
#include<SDL.h>

struct Texture
{
	SDL_Texture* tex = NULL;
	int          w;
	int          h;
	SDL_Rect     dstrect;
};

struct Menu
{
	Texture textures;
	SDL_Rect drawRect;
};

struct Background
{
	SDL_Texture* tex;
	SDL_Rect rect;
};

struct Creep
{
	SDL_Texture* tex;
	SDL_Rect anim;		 int xAnim, yAnim;
	SDL_Rect damageRect;  SDL_Rect healthRect; int health;
	int xWay, yWay;
	bool active;
	bool inZone;
};

struct Tower
{
	int index;

	SDL_Texture* tex;
	SDL_Rect anim;
	SDL_Rect spawn;

	int rad;

	int lock;

	SDL_Texture* shot_tex;
	SDL_Rect shot_anim;
	SDL_Rect bullet;
	int timer;//пока не сделал
	bool shot_spawn;	

	int dist;

	int damage;
};

struct Places
{
	SDL_Rect p1 = { 340,183,150,100 };
	SDL_Rect p2 = { 920,183,150,100 };
	SDL_Rect p3 = { 128,363,150,100 };
	SDL_Rect p4 = { 594,363,150,100 };
};

struct Shop
{
	SDL_Texture* tex;
	SDL_Rect spawn;
	SDL_Rect anim;
};

struct Shopbg
{
	SDL_Texture* tex;
	SDL_Rect anim;
	SDL_Rect spawn;
};

struct Shot
{
	SDL_Texture* tex;
	SDL_Rect anim;

	SDL_Rect bullet;

	int timer;

	bool spawn;
};

struct Score
{
	Texture textures;
	SDL_Rect drawRect;
};