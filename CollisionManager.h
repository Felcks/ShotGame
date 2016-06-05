#include <SDL2/SDL.h>

SDL_Rect Collision_Rect_Screen(SDL_Rect rect, int ScreenWidth, int ScreenHeight);

int Collision_Rect_Screen_Bool(SDL_Rect rect, int ScreenWidth, int ScreenHeight);

int Collision_Rect_Rect(SDL_Rect, SDL_Rect);

SDL_Rect Collision_Rect_Rect_Rect(SDL_Rect rect, SDL_Rect rect2);
