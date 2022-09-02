#include<iostream>
#include"structs.h"
#include"menu.h"
int damageClick = 50;

Score score;
char score_char[12] = { "Score: 0" };

void InitScore()
{
	score.textures = loadFont(score_char, "fonts\\Chava-Regular.ttf", { 0,0,180,255 }, 25);
	score.drawRect = { 0,0,200,30 };

}

void ScoreUpdate()
{
	char message[12];
	sprintf_s(message, 12, "%s%d", );
}

void DrawScore()
{
	SDL_RenderCopy(ren, str_tex, null, &str_rect);
}

void ClickCreep(int i, int mouse_x, int mouse_y, bool& mousebtdown, Creep* creeps)
{
	/*position*/if (mousebtdown == true and mouse_x >= creeps[i].xWay and mouse_x <= creeps[i].xWay + 42 and mouse_y >= creeps[i].yWay and mouse_y <= creeps[i].yWay + 84)
		/*health*/if (creeps[i].health > 0)
		{
			creeps[i].health = creeps[i].health - damageClick;
			mousebtdown = false;
		}
}