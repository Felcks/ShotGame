#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	SDL_Rect rect;
	SDL_Texture* texture;
	SDL_Rect lifeRect;
	SDL_Texture* lifeTexture;
	SDL_Rect lifeRectBG;
	SDL_Texture* lifeTextureBG;
	SDL_Rect imageRecort;
	float speed;
	int directionH;
	int directionV;
	int hp;
	int vulnerable; // bool (0 or 1) that says player is or isn't vunerable
	int countVulnerable; //When player vunarable count to minVunerable ir order to make player vunarable again
	int minToVulnerable;
	int canShoot;
	double rotationDegrees;
	int indexSprite;
	int spritePosY[8];
	int countSprite; 
} PLAYER;

void DrawPlayer(PLAYER player, SDL_Renderer* windowRenderer);


