//
//
//
//
//						TODO:
//							-Implement operators some operators in Vector3, check Vector3 class.
//							
//
//
//
#include <iostream>
#include "SDL.h"
#include "Window.h"
#include "Bitmap.h"
#include "ErrorReport.h"

#define WIDTH 1600
#define HEIGHT 900


int main(int argc, char ** argv)
{

	int initSuccess = SDL_Init(SDL_INIT_EVERYTHING);
	//Error Checking Code.
	if(initSuccess != 0)
	{
		ErrorReport::WriteToLog("SDL_Init");
		return 1;
	}

	Window window = Window("Software Renderer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

	Bitmap pixels = Bitmap(window.GetWindowWidth(),window.GetWindowHeight());
	bool quit = false;
	SDL_Event event;
	
	while (!quit)
    {	
		
		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering

		//1.Events
		while(SDL_PollEvent(&event))
		{
			if( event.type == SDL_QUIT )
			{
				quit = true;																					
			}
		}
		//2.Logic

		//3.Rendering
		SDL_UpdateTexture(window.GetTexture(), NULL ,pixels.GetPixels(),WIDTH * 4 * sizeof(char));
        SDL_RenderClear(window.GetRenderer());
		SDL_RenderCopy(window.GetRenderer(), window.GetTexture(), NULL, NULL);
        SDL_RenderPresent(window.GetRenderer());
    }

    SDL_DestroyTexture(window.GetTexture());
    SDL_DestroyRenderer(window.GetRenderer());
    SDL_DestroyWindow(window.GetWindow());
    SDL_Quit();

    return 0;
}
