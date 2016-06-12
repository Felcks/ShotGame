#include "Window.h"

void CreateWindow(WINDOW* window, char gameTitle[50], int screenWidth, int screenHeight)
{
	(*window).SDLwindow = NULL;
	(*window).renderer = NULL;

	uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	(*window).SDLwindow = SDL_CreateWindow( gameTitle , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

	if( (*window).SDLwindow == NULL )
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );   
    else{
        (*window).width = screenWidth;
        (*window).height = screenHeight;
        (*window).renderer = SDL_CreateRenderer( (*window).SDLwindow, -1, SDL_RENDERER_ACCELERATED );    

        SDL_RenderSetLogicalSize((*window).renderer, (*window).width, (*window).height);
    }

    (*window).mouseFocus = 1;
	(*window).keyboardFocus = 1;
    (*window).fullScreen = 0;
    (*window).minimized = 0;
    (*window).aspectRatio = screenWidth/screenHeight;
}

void WindowHandleEvent(SDL_Event e, WINDOW* window)
{
	if(e.type == SDL_WINDOWEVENT){
		switch( e.window.event )
        {
            //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
	            (*window).width = e.window.data1;
	            (*window).height = e.window.data2;
	            SDL_RenderPresent( (*window).renderer );
	            (*window).aspectRatio = (*window).width/ (*window).height;
            	break;

            //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
	            SDL_RenderPresent( (*window).renderer );
	            break;
	        //Mouse entered Window
	        case SDL_WINDOWEVENT_ENTER:
           	 	(*window).mouseFocus = 1;
            break;
            //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
            	(*window).mouseFocus = 0;
            break;
            //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
           		(*window).minimized = 1;
            break;
            //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
            	(*window).minimized = 0;
            break;
            //Window restored
            case SDL_WINDOWEVENT_RESTORED:
            	(*window).minimized = 0;
            break;
	    }
	}
	else if( e.type == SDL_KEYDOWN)
    {
    	 const Uint8 *keystates = SDL_GetKeyboardState( NULL );
    	 if(keystates[ SDL_SCANCODE_RETURN] &&keystates[ SDL_SCANCODE_LCTRL]){
	        if( (*window).fullScreen == 1 )
	        {
	            SDL_SetWindowFullscreen((*window).SDLwindow, SDL_FALSE );
	            (*window).fullScreen = 0;
	        }
	        else
	        {
	            SDL_SetWindowFullscreen((*window).SDLwindow, SDL_TRUE );
	            (*window).fullScreen = 1;
	            (*window).minimized = 0;
	        }
	    }
    }
}

void WindowClose(WINDOW* window) // --> Não implementada em nenhuma parte do código lembrar de implementar @@!!@@$@%%%%$$$$$$#######
{
	/*
    //Free loaded images
    gSceneTexture.free();

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    gWindow.free();

    //Quit SDL subsystems*/
    IMG_Quit();
    SDL_Quit();
}