#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <math.h>
//#define M_PI acos(-1.0)

#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "MonoBehaviour.h"
#include "Font.h"

/*#ifndef WINDOW_H__
#define WINDOW_H__
#endif 
#include "Window.h"*/

#define SCREEN_WIDTH 800   
#define SCREEN_HEIGHT  600
#define GAME_TITLE "JOGO DE TIRO"

//WAVES
#define WAVE1  5
#define WAVE2  10
#define WAVE3  12
#define WAVE4  15
#define WAVE5  20

SDL_Texture* backgroundTexture = NULL;

void CreateComponents();
void CreateFont();
void loadFromRenderedText();
SDL_Texture* loadTexture( char* path);


void Draw();
void Update();
void Collision();
void UpdateKeyBoard();
void UpdateShotPosition();
void PlayerVunerability();
void CreateEnemy();
void CreateBoss();
void RemoveAt_Shot(ARRAYSHOT *arrayShot, int pos);
void RemoveAt_Enemy(ARRAYENEMY *arrayEnemy, int pos);
void CreateRound();
void GameOver();
void Shoot(float directionH, float directionV);
void LookAtMouse(PLAYER* player, VECTOR2 mousePos);
VECTOR2 GetMousePos();
void AnimPlayer();
void AnimateEnemy();


int quit = 0;
SDL_Event e;
int gameDelay = 8;
int score = 0;
int wavesurvived = 0;
int totalwaves = 0;
int isboss = 0;
int bossdamage = 0;

WINDOW window;

int rand(void);
time_t t;

PLAYER player;
ARRAYSHOT arrayShot;
ARRAYENEMY arrayEnemy;
FONT font;


TTF_Font *scoreFont = NULL;
SDL_Texture *scoreTexture = NULL;
SDL_Rect fontRect;

//Loops Variables
int i, j;


int main(void)
{

    CreateWindow(&window, GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);


	CreateComponents();
    CreateFont();



    //int w, h;
    //SDL_GetWindowSize(window, &w, &h);

    backgroundTexture = loadTexture("Sprites/BackgroundMenu.png");

    

	while(quit == 0)
    {
		while( SDL_PollEvent( &e ) != 0 )
        {
	        if( e.type == SDL_QUIT )
            {
	            quit = 1;
	        }

            WindowHandleEvent(e, &window);

            VECTOR2 mousePos = GetMousePos();
            LookAtMouse(&player, mousePos);

            if(e.type == SDL_MOUSEBUTTONDOWN){

                VECTOR2 playerPos;
                playerPos.x = player.rect.x;
                playerPos.y = player.rect.y;
   

                player.canShoot = 0;
                VECTOR2 dir = GetVector(playerPos, mousePos);
                dir = Normalize(dir);
                Shoot(dir.x, dir.y);
            }
            if(e.type == SDL_MOUSEBUTTONUP && player.canShoot == 1 ){
                player.canShoot = 1;
            }
        }

        SDL_Delay(gameDelay);
      
        player.lifeRect.x = player.rect.x + 2;
        player.lifeRect.y = player.rect.y - 10;
        player.lifeRectBG.x = player.rect.x + 2;
        player.lifeRectBG.y = player.rect.y - 10;
        player.lifeRect.w = player.hp;

        if (player.hp < 15 && player.hp > 6)
        {
        	player.lifeTexture = loadTexture("Sprites/Life2.png");
        }

        else if (player.hp < 7)
        {
        	player.lifeTexture = loadTexture("Sprites/Life3.png");
        }

        Update();
        Draw();       
	}
}

void Draw()
{
    if(window.minimized == 1)
        return;

    //Screen
    SDL_SetRenderDrawColor( window.renderer, 0000, 0000, 0000, 0000 );
    SDL_RenderClear(window.renderer);
    //DrawBackground
    SDL_RenderCopy( window.renderer, backgroundTexture, NULL, NULL );
    //Draw Player 
    DrawPlayer(player, &window);
     //Draw Shot
    for( i=0; i<arrayShot.length; i++)
         SDL_RenderCopy( window.renderer, arrayShot.defaultShotTexture, NULL, &arrayShot.vetor[i].rect );
    //Draw Enemies
    for( j=0; j<arrayEnemy.length; j++)
         SDL_RenderCopyEx( window.renderer, arrayEnemy.vetor[j].texture, &arrayEnemy.vetor[j].imageRect, &arrayEnemy.vetor[j].rect, 0, NULL, SDL_FLIP_NONE);
    //Draw Font
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    char scoreText[100];
    sprintf(scoreText, "%i", score);
    loadFromRenderedText(scoreText, textColor);
    SDL_RenderCopy( window.renderer, scoreTexture, NULL, &fontRect);
   

    SDL_RenderPresent(window.renderer); 
}

void Update()
{
    UpdateKeyBoard();
    UpdateShotPosition();
    PlayerVunerability();
    GameOver();
    CreateRound();
    Collision();
    AnimateEnemy();
}

void Collision()
{
    player.rect = Collision_Rect_Screen(player.rect, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Collision Shot and Enemy
    for(j = 0; j<arrayEnemy.length; j++){
        for( i = 0; i<arrayShot.length; i++){

            if(Collision_Rect_Rect(arrayEnemy.vetor[j].rect, arrayShot.vetor[i].rect) == 1){
                
                if(isboss == 1)
                {
                    RemoveAt_Shot(&arrayShot, i);
                    bossdamage ++;

                    if(bossdamage == 10)
                    {
                        RemoveAt_Enemy(&arrayEnemy, j);
                        isboss = 0;
                        score += 10;
                        bossdamage = 0;
                    }
                }
                else if (isboss == 0){
                RemoveAt_Enemy(&arrayEnemy, j);
                RemoveAt_Shot(&arrayShot, i);
                score++;
                }
            }
        }
    }

     //Collison Enemy_border + follow player
    for(j = 0; j< arrayEnemy.length; j++){
       // arrayEnemy.vetor[j].rect = Collision_Rect_Screen(arrayEnemy.vetor[j].rect, SCREEN_WIDTH, SCREEN_HEIGHT);

        arrayEnemy.vetor[j].rect = ChasePlayer(arrayEnemy.vetor[j].rect, player.rect, &arrayEnemy.vetor[j]);
    }

     //Collision Enemy_Player
    for(j = 0; j<arrayEnemy.length; j++){        
       if(Collision_Rect_Rect(player.rect, arrayEnemy.vetor[j].rect) == 1 && player.vulnerable == 1){
            if (isboss == 1){
            player.hp -= 10;
            player.vulnerable = 0;

            }

            else if (isboss == 0)
            {
                if (wavesurvived >= 3)
                {
                player.hp -= 2;
                player.vulnerable = 0;
                }
                else
                {
                   player.hp --;
                   player.vulnerable = 0; 
                }

            }
       }
    }

    //Collision Shot_Border
    for(i=0; i<arrayShot.length; i++){
        if(Collision_Rect_Screen_Bool(arrayShot.vetor[i].rect, SCREEN_WIDTH, SCREEN_HEIGHT) == 1){
            RemoveAt_Shot(&arrayShot, i);
        }   
    }
}

void LookAtMouse(PLAYER* player, VECTOR2 mousePos)
{
  //  printf("%i\n",mousePos );
    int x = mousePos.x - (*player).rect.x;
    int y = mousePos.y - (*player).rect.y;
    double angle = atan2(y,x);
    (*player).rotationDegrees = (angle * 180/ M_PI);
}

VECTOR2 GetMousePos()
{
    //MOUSE MOTION -- EVENTO
    VECTOR2 mousePos;
    mousePos.x = 0;
    mousePos.y = 0;
    SDL_GetMouseState( &mousePos.x, &mousePos.y);

    return mousePos;
}

//Returns a copy of array with length - 1 (Removes the element on index i);
void RemoveAt_Shot(ARRAYSHOT *arrayShot, int pos)
{
    SHOT copy[(*arrayShot).length-1];

    int oldArrayPos = 0;
    int newArrayPos = 0;
    for(oldArrayPos=0; oldArrayPos<(*arrayShot).length; oldArrayPos++){
        if(oldArrayPos != pos){
             copy[newArrayPos] = (*arrayShot).vetor[oldArrayPos];
             newArrayPos++;
        }
    }

    (*arrayShot).length--;
    for(j=0; j<(*arrayShot).length; j++){
        (*arrayShot).vetor[j] = copy[j];
    }
}

//Returns a copy of array with length - 1 (Removes the element on index i);
void RemoveAt_Enemy(ARRAYENEMY *arrayEnemy, int pos)
{
    ENEMY copy[(*arrayEnemy).length-1];

    int oldArrayPos = 0;
    int newArrayPos = 0;
    for(oldArrayPos=0; oldArrayPos<(*arrayEnemy).length; oldArrayPos++){
        if(oldArrayPos != pos){
             copy[newArrayPos] = (*arrayEnemy).vetor[oldArrayPos];
             newArrayPos++;
        }
    }

    (*arrayEnemy).length--;
    for(j=0; j<(*arrayEnemy).length; j++){
        (*arrayEnemy).vetor[j] = copy[j];
    }
}


int posVector[24];
void CreateRound(){



    for(i = 0; i< 24 ; i++)
        posVector[i] = 0;

    if (wavesurvived >= 5)
    {
    	totalwaves += wavesurvived;
    	wavesurvived -= 5;
    }

    if(arrayEnemy.length == 0){
       
        if (wavesurvived == 0){

        	for(i=0; i<WAVE1; i++){
            CreateEnemy();
           	}
            wavesurvived ++;
        }
        else if (wavesurvived == 1){

        	for(i=0; i<WAVE2; i++){
            CreateEnemy();
            }
            wavesurvived ++;
        }
        else if (wavesurvived == 2){

        	CreateBoss();

            
            wavesurvived ++;
        
         }
         else if (wavesurvived == 3){

        	for(i=0; i<WAVE4; i++){
            CreateEnemy();
            }
            wavesurvived ++;
         }
         else if (wavesurvived == 4){

        	for(i=0; i<WAVE5; i++){
            CreateEnemy();
            }
            wavesurvived ++;
        
         }

    }

    
    
    
}
void GameOver(){
    if(player.hp <= 0){
        
        score = 0;
        wavesurvived = 0;
        
        CreateComponents();
    }
}


void CreateEnemy()
{
    int x[4] = {365, -30, 365, SCREEN_WIDTH + 30};
    int y[4] = {-30, 250, SCREEN_HEIGHT + 30, 250};
    int quad;
    int pos;
    int sortedNumber;

     do{
            sortedNumber = rand() % 24;
            pos = sortedNumber % 6;
            quad = sortedNumber / 6;
    }while(posVector[sortedNumber]);

        posVector[sortedNumber] = 1;

        if(quad % 2 == 1){
        x[quad] -= pos%3 * 41;
        y[quad] += pos/3 * 20;
    }
    else {
        y[quad] -= pos%3 * 41;
        x[quad] += pos/3 * 20;
    }
        


    
    
    ENEMY enemy;
    enemy.rect.x = x[quad];
    enemy.rect.y = y[quad];
    enemy.rect.w = 41;
    enemy.rect.h = 32;
    enemy.speedH = 1;
    enemy.speedV = 1;
    enemy.texture = loadTexture("Sprites/ghost.png");
    enemy.countIA = 0;
    enemy.imageRect.x = 0;
    enemy.imageRect.y = 0;
    enemy.spritePos = rand() % 3;
    enemy.imageRect.w =  16;
    enemy.imageRect.h = 16;
    enemy.spriteMax = 2;
    enemy.delaySprite = 0;
    

    if (totalwaves >= 5)
    {
        enemy.speedH = 2;
        enemy.speedV = 2;
    }
 
    if (wavesurvived >= 3)
    {
        enemy.texture = loadTexture("Sprites/skeleton.png");  
        enemy.spriteMax = 3;
        enemy.spritePos = rand() % 3;
    }

  

    arrayEnemy.vetor[arrayEnemy.length] = enemy;
    arrayEnemy.length++;
    
}

void CreateBoss()
{
    int x[4] = {365, -30, 365, SCREEN_WIDTH + 30};
    int y[4] = {-30, 250, SCREEN_HEIGHT + 30, 250};
    int quad;
    int pos;
    int sortedNumber;

     do{
            sortedNumber = rand() % 24;
            pos = sortedNumber % 6;
            quad = sortedNumber / 6;
    }while(posVector[sortedNumber]);

        posVector[sortedNumber] = 1;

        if(quad % 2 == 1){
        x[quad] -= pos%3 * 41;
        y[quad] += pos/3 * 20;
    }
    else {
        y[quad] -= pos%3 * 41;
        x[quad] += pos/3 * 20;
    }
        


    
    
    ENEMY enemy;
    enemy.rect.x = x[quad];
    enemy.rect.y = y[quad];
    enemy.rect.w = 41;
    enemy.rect.h = 32;
    enemy.speedH = 2;
    enemy.speedV = 2;
    enemy.texture = loadTexture("Sprites/bat.png");
    enemy.countIA = 0;
    enemy.imageRect.x = 0;
    enemy.imageRect.y = 0;
    enemy.spritePos = rand() % 3;
    enemy.imageRect.w =  16;
    enemy.imageRect.h = 16;
    enemy.spriteMax = 2;
    enemy.delaySprite = 0;

    isboss = 1;
    
  

    arrayEnemy.vetor[arrayEnemy.length] = enemy;
    arrayEnemy.length++;

    
}



void AnimateEnemy(){
    for(i = 0; i < arrayEnemy.length; i++){
        ENEMY* enemy = &(arrayEnemy.vetor[i]);

        (*enemy).delaySprite ++;
        if((*enemy).delaySprite > 20){
            (*enemy).delaySprite = 0;
        


           (*enemy).spritePos++;

           if((*enemy).spritePos >= (*enemy).spriteMax)
            (*enemy).spritePos = 0;

            (*enemy).imageRect.x = 16 + ((*enemy).spritePos * 16);
            }
    }
}

void PlayerVunerability(){
    if(player.vulnerable == 0){
        player.countVulnerable++;
        if(player.countVulnerable > player.minToVulnerable){
            player.countVulnerable = 0;
            player.vulnerable = 1;
        }
    }
}

void UpdateShotPosition(){
    for(i=0; i<arrayShot.length; i++){
        arrayShot.vetor[i].rect.x += arrayShot.vetor[i].currentSpeedH;
        arrayShot.vetor[i].rect.y += arrayShot.vetor[i].currentSpeedV;
    }
}

void Shoot(float directionH, float directionV)
{
    SHOT shot;
    shot.rect.x = player.rect.x;
    shot.rect.y = player.rect.y;
    shot.rect.w = arrayShot.defaultShotSize;
    shot.rect.h = arrayShot.defaultShotSize;

    shot.currentSpeedH = arrayShot.defaultShotSpeed * directionH;
    shot.currentSpeedV = arrayShot.defaultShotSpeed * directionV;

    arrayShot.vetor[arrayShot.length] = shot;
    arrayShot.length++;
    arrayShot.delay = 0;
}



void UpdateKeyBoard()
{
        const Uint8 *keystates = SDL_GetKeyboardState( NULL );

        if(keystates[ SDL_SCANCODE_ESCAPE ]){
            quit = 1;
        }

        int moved = 0;

        if(keystates[ SDL_SCANCODE_D] ){
            player.rect.x += player.speed;
            player.directionH = 1;
            player.directionV = 0;
            moved = 1;

            AnimPlayer(&player);
        }
        else if(keystates[ SDL_SCANCODE_A] ){
            player.rect.x += -player.speed;
            player.directionH = -1;
            player.directionV = 0;
            moved = 1;

             AnimPlayer(&player);
        }

        if(keystates[ SDL_SCANCODE_W] ){
            player.rect.y += -player.speed;
            player.directionV = -1;
            if(moved == 0)
                player.directionH = 0;


            AnimPlayer(&player);      
        }
        
        else if(keystates[ SDL_SCANCODE_S] ){
            player.rect.y += player.speed;
            player.directionV = 1;
            if(moved == 0)
                player.directionH = 0;

            AnimPlayer(&player);
        }

        
       
    arrayShot.delay++;
    if(keystates[ SDL_SCANCODE_UP] && keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(2, -2);    
    }
    else if(keystates[ SDL_SCANCODE_UP] && keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(-2, -2);    
    }
    else if(keystates[ SDL_SCANCODE_DOWN] && keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {        
        Shoot(-2, 2);    
    }
    else if(keystates[ SDL_SCANCODE_DOWN] && keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {   
        Shoot(2, 2);    
    }

    else if(keystates[ SDL_SCANCODE_UP] && arrayShot.delay >= arrayShot.delayMin)
    {       
        Shoot(0, -2);     
    }  
    else if(keystates[ SDL_SCANCODE_DOWN] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(0, 2 );     
    } 
    else if(keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(2, 0 );     
    }  
    else if(keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(-2, 0 );     
    }  

}

void AnimPlayer(PLAYER* player)
{
    (*player).countSprite++;
    if((*player).countSprite < 10)
        return;

    (*player).indexSprite++;
    (*player).countSprite = 0;

    if((*player).indexSprite > 7)
            (*player).indexSprite = 0;
}

void CreateComponents(){


    player.rect.x = SCREEN_WIDTH / 2 - 47/2;
    player.rect.y = SCREEN_HEIGHT / 2 - 22/2;
    player.rect.w = 47;
    player.rect.h = 22;
    player.speed = 2;
    player.texture = loadTexture("Sprites/PlayerSprite1.png");
    player.lifeTexture = loadTexture("Sprites/Life.png");
    player.lifeTextureBG = loadTexture("Sprites/Life_BG.png");
    player.hp = 34;
    player.lifeRect.x = player.rect.x + 5;
    player.lifeRect.y = player.rect.y - 10;
    player.lifeRect.w = player.hp;
    player.lifeRect.h = 10;
    player.vulnerable = 1;
    player.minToVulnerable = 50;
    player.countVulnerable = 0;
    player.rotationDegrees = 0;
    player.countSprite = 0;


    //memset(player.spritePosY, 0, sizeof(player.spritePosY));
   
    player.spritePosY[0] = 0;
    player.spritePosY[1] = 33;
    player.spritePosY[2] = 67;
    player.spritePosY[3] = 99;
    player.spritePosY[4] = 132;
    player.spritePosY[5] = 166;
    player.spritePosY[6] = 198;
    player.spritePosY[7] = 231;
    
    player.indexSprite = 0;
    player.imageRecort.x = 4;
    player.imageRecort.y = player.spritePosY[player.indexSprite];
    player.imageRecort.w = 47;
    player.imageRecort.h = 22;

    player.lifeRectBG.x = player.rect.x + 5;
    player.lifeRectBG.y = player.rect.y - 10;
    player.lifeRectBG.w = 35;
    player.lifeRectBG.h = 10;

    arrayShot.defaultShotSize = 20;
    arrayShot.defaultShotSpeed = 2;
    arrayShot.defaultShotTexture = loadTexture("Sprites/Shot.png");
    arrayShot.length = 0;
    arrayShot.delay = 0;
    arrayShot.delayMin = 50;

    arrayEnemy.length = 0;
}

SDL_Texture* loadTexture( char* path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
       printf("#Erro ao carregar imagem!\n");
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( window.renderer, loadedSurface );
        if( newTexture == NULL )
        {
           printf("#Erro ao carregar imagem!\n");
       	}

        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}



void CreateFont()
{
    fontRect.x = 5;
    fontRect.y = 5;
    fontRect.w = 25;
    fontRect.h = 25;

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    scoreFont = TTF_OpenFont( "Fonts/Score_Font.TTF", 28 );
    if( scoreFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        
    }
    else
    {
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        char scoreText[100];
        sprintf(scoreText, "%i", score);
        loadFromRenderedText(scoreText, textColor);
        if( scoreTexture == NULL )
        {
            printf( "Failed to render text texture!\n" );
        }
    }
}

void loadFromRenderedText( char text[100], SDL_Color textColor )
{
    //Render text suface
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, text, textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        scoreTexture = SDL_CreateTextureFromSurface( window.renderer, textSurface );
        if( scoreTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
          //  mWidth = textSurface->w;
          //  mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}
