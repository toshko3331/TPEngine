#include <iostream>
#include "HeadersInclude.h"
#define WIDTH 640 
#define HEIGHT 700 


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
	//// Temporary Variables for Testing Code  ///	
	Vertex v1 = Vertex(Vector4f(110,100,0,0));
	Vertex v2 = Vertex(Vector4f(50,200,0,0));
	Vertex v3 = Vertex(Vector4f(20,700,0,0));

	//// End of Temporary Variables ////	
	Rasterizer rasterizer = Rasterizer(&pixels);
	while (!quit)
	{	

		SDL_UpdateTexture(window.GetTexture(), NULL ,pixels.GetPixels(),WIDTH *  sizeof(Uint32));	

	

		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering
		//Just some test code for the Horizontal Line drawing.		
		rasterizer.RasterizeTriangle(v1,v2,v3);
		
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
