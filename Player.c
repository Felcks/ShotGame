#include "Player.h"


void DrawPlayer(PLAYER player, SDL_Renderer* window_Renderer)
{
	SDL_Point playerImage;
    playerImage.x = 0 + player.rect.w/2;
    playerImage.y = 0 + player.rect.h/2;
    

    player.imageRecort.y = player.spritePosY[player.indexSprite];
    SDL_RenderCopyEx( window_Renderer, player.texture, &player.imageRecort, &player.rect, player.rotationDegrees, &playerImage, SDL_FLIP_NONE  );
    SDL_RenderCopy( window_Renderer, player.lifeTexture, NULL, &player.lifeRect );
    SDL_RenderCopy( window_Renderer, player.lifeTextureBG, NULL, &player.lifeRectBG );
}
