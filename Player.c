#include "Player.h"

void DrawPlayer(PLAYER player, WINDOW* window)
{
	SDL_Point playerImage;
    playerImage.x = 0 + player.rect.w/2;
    playerImage.y = 0 + player.rect.h/2;
    

    player.imageRecort.y = player.spritePosY[player.indexSprite];
    player.rect.w *= (*window).aspectRatio;
    player.rect.h *= (*window).aspectRatio;
    SDL_RenderCopyEx( (*window).renderer, player.texture, &player.imageRecort, &player.rect, player.rotationDegrees, &playerImage, SDL_FLIP_NONE  );
    SDL_RenderCopy( (*window).renderer, player.lifeTexture, NULL, &player.lifeRect );
    SDL_RenderCopy( (*window).renderer, player.lifeTextureBG, NULL, &player.lifeRectBG );
}
