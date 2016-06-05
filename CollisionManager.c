#include "CollisionManager.h"


SDL_Rect Collision_Rect_Screen(SDL_Rect rect, int ScreenWidth, int ScreenHeight){
	
	if (rect.x < 0){
		rect.x = 0;
	}

	if (rect.x + rect.w > ScreenWidth){
		rect.x = ScreenWidth - rect.w;
	}

	if (rect.y < 0){
		rect.y = 0;
	}

	if (rect.y + rect.h > ScreenHeight){
		rect.y = ScreenHeight - rect.h;
	}

	return rect;
}

SDL_Rect Collision_Rect_Rect_Rect(SDL_Rect rect, SDL_Rect rect2)
{
	rect.x = rect2.x + rect2.w;
	rect.y = rect2.y + rect2.h;

	return rect;
}

int Collision_Rect_Screen_Bool(SDL_Rect rect, int ScreenWidth, int ScreenHeight){
	
	if (rect.x < 0)
		return 1;
	
	if (rect.x + rect.w > ScreenWidth)
		return 1;
	
	if (rect.y < 0)
		return 1;
	
	if (rect.y + rect.h > ScreenHeight)
		return 1;
	

	return 0;
}

int Collision_Rect_Rect(SDL_Rect rect1, SDL_Rect rect2){
	if(rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w &&
		rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h){
		return 1;
	}
	return 0;
}

