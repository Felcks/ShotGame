#include "Window.h"

void CreateWindow(WINDOW* window, char gameTitle[50], int screenWidth, int screenHeight)
{
	(*window).SDLwindow = NULL;
	(*window).renderer = NULL;

	uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
	(*window).SDLwindow = SDL_CreateWindow( gameTitle , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if( (*window).SDLwindow == NULL )
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    
    else
        (*window).renderer = SDL_CreateRenderer( (*window).SDLwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );    

}