#include <iostream>
#include "HeadersInclude.h"
//Temporary include calls
#include <time.h>
#include <math.h>
//End of temporary include calls

#define WIDTH 1200 
#define HEIGHT 800 


int main(int argc, char ** argv)
{

	int initSuccess = SDL_Init(SDL_INIT_EVERYTHING);
	//Error Checking Code.
	if(initSuccess != 0)
	{
		ErrorReport::WriteToLog_SDL("SDL_Init");
		return 1;
	}
		
	Window window = Window("Software Renderer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

	Bitmap pixels = Bitmap(window.GetWindowWidth(),window.GetWindowHeight());
	bool quit = false;
	SDL_Event event;
	//// Temporary Variables for Testing Code  ///	
	srand(time(NULL));
	//Load the level and it's objects.
	OBJLevel level("monkey.obj");	
	//Get the objects from the level.
	std::vector<Object>& objects = level.GetObjects();
	//Load all textures through the bitmap class, but for now use the random texture.
	Bitmap texture = Bitmap(32,32);
	for(int i = 0;i < texture.GetHeight();i++)
	{
		for(int j = 0;j < texture.GetWidth();j++)
		{
			texture.SetPixel(j,i,rand()%255,rand()%255,rand()%255,rand()%255);	
		}	
	}
	Rasterizer rasterizer = Rasterizer(&pixels,&texture);
	//// End of Temporary Variables ///
	Camera camera(WIDTH,70,(float)pixels.GetWidth()/pixels.GetHeight(),0.1,1000,Matrix4f().InitializeIdentity().Translate(Vector3f(0,0,3)));
	
	//We might not need this method anymore	
	if(SDL_SetRelativeMouseMode(SDL_TRUE) != 0)
	{
		ErrorReport::WriteToLog_SDL("SDL_SetRelativeMouseMode");
	}
	SDL_ShowCursor(0);
	while (!quit)
	{	
		SDL_UpdateTexture(window.GetTexture(), NULL ,pixels.GetPixels(),WIDTH * sizeof(Uint32));	
		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering
		pixels.Clear(128);		
		rasterizer.RasterizeObjMesh(camera.GetMatrix(),objects.at(0),level);
		//1.Events
		while(SDL_PollEvent(&event))
		{
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
			//TODO:Pre-Compute these outside of the loop.
			camera.UpdateCamera(&event);
//			SDL_WarpMouseInWindow(window.GetWindow(),(int)(WIDTH/2),(int)(HEIGHT/2));
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
