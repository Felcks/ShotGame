#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	TTF_Font *TFF;
	SDL_Texture *texture;
	SDL_Rect rect;

} FONT;