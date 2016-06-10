#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect rect;
	SDL_Rect imageRect;
	int spritePos;
	int spriteMax;
	int countSprite;
	int delaySprite;
	SDL_Texture* texture;
	int speedH;
	int speedV;
	int directionH;
	int directionV;
	int countIA;
} ENEMY;


typedef struct {
	ENEMY vetor[100];
	int length;
} ARRAYENEMY; 

SDL_Rect ChasePlayer(SDL_Rect enemyRect, SDL_Rect playerRect, ENEMY* enemy);
