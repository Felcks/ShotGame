#include <SDL2/SDL.h>

typedef struct {
	int x;
	int y;
} VECTOR2;

VECTOR2 Normalize(VECTOR2 vector);

VECTOR2 GetVector(VECTOR2 vector1, VECTOR2 vector2);

double Degree(VECTOR2 vector1, VECTOR2 vector2);

VECTOR2 Translate(VECTOR2 vector, VECTOR2 vectorSum);