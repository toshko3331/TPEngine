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
#include "HeadersInclude.h"
#define WIDTH 640 
#define HEIGHT 400 


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
	int i = 0; // Temporary 'i' variable for testing code.
	Rasterizer rasterizer = Rasterizer();
	while (!quit)
	{	
	
		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering
		//Just some test code for the Horizontal Line drawing.
		if(i < HEIGHT && i%2 == 0)
		{
			rasterizer.DrawHorizontalLine(Vertex(Vector4f(0,i,0,0)),Vertex(Vector4f(WIDTH,i,0,0)),&pixels);
		}
		else if(i >= HEIGHT)
		{
			SDL_Delay(2000);
			quit = true;
		}
		i++;
		//End of test code.
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
