#include "Enemy.h"

SDL_Rect ChasePlayer(SDL_Rect enemyRect, SDL_Rect playerRect, ENEMY* enemy)
{
	(*enemy).countIA++;
	if((*enemy).countIA <= 2)
		return enemyRect;

	(*enemy).countIA = 0;

	if(enemyRect.x < playerRect.x)
		enemyRect.x++;
	else
		enemyRect.x--;

	if(enemyRect.y < playerRect.y)
		enemyRect.y++;
	else
		enemyRect.y--;

	return enemyRect;
}