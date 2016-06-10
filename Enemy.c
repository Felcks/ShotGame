#include "Enemy.h"

SDL_Rect ChasePlayer(SDL_Rect enemyRect, SDL_Rect playerRect, ENEMY* enemy)
{
	(*enemy).countIA++;
	if((*enemy).countIA <= 2)
		return enemyRect;

	(*enemy).countIA = 0;

	if(enemyRect.x < playerRect.x)
		enemyRect.x += (*enemy).speedH;
	else
		enemyRect.x -= (*enemy).speedH;

	if(enemyRect.y < playerRect.y)
		enemyRect.y += (*enemy).speedV;
	else
		enemyRect.y -= (*enemy).speedV;

	return enemyRect;
}