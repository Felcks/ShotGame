#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	SDL_Window* SDLwindow;
	SDL_Renderer* renderer;
	float aspectRatio;
	int mouseFocus;
	int keyboardFocus;
    int fullScreen;
    int minimized;
	int width;
	int height;

} WINDOW;


void CreateWindow(WINDOW* window, char gameTitle[50], int screenWidth, int screenHeight);

void WindowHandleEvent(SDL_Event e, WINDOW* window);

void WindowClose(WINDOW* window);