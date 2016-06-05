#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	SDL_Window* SDLwindow;
	SDL_Renderer* renderer;
	int mouseFocus;
	int keyboardFocus;
	int width;
	int height;
} WINDOW;


void CreateWindow(WINDOW* window, char gameTitle[50], int screenWidth, int screenHeight);