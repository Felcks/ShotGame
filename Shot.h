#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect rect;
	SDL_Texture* texture;
	float currentSpeedH;
	float currentSpeedV;
	float directionH;
	float directionV;

} SHOT;

typedef struct {
	SHOT vetor[100];
	int length;
	float defaultShotSpeed;
	SDL_Texture* defaultShotTexture;
	int defaultShotSize;
	int delay;
	int delayMin;
} ARRAYSHOT; 


/*void RemoveAt_Shot(ARRAYSHOT *arrayShot, int i)
{
    SHOT copy[(*arrayShot).length-1];
    int adicionador = 0;
    int j = 0;
    for( adicionador = 0; adicionador<(*arrayShot).length; j++){
        if(adicionador != i ){
            copy[j] = (*arrayShot).vetor[adicionador];
            adicionador++;
        }
        else if(adicionador == i){
            j--;
            adicionador++;
        }

    }
    
    (*arrayShot).length--;
    for(int a=0; a<(*arrayShot).length; a++){
        (*arrayShot).vetor[a] = copy[a];
    }
}
*/
