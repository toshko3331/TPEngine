#include <iostream>
#include "HeadersInclude.h"

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
		
	Window window = Window("Inaniloquent Lamprophony",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

	Bitmap pixels = Bitmap(window.GetWindowWidth(),window.GetWindowHeight());
	bool quit = false;
	SDL_Event event;
	//Load the level and it's objects.
	OBJLevel level("Cube.obj");
	//Load all of the textures.
	std::vector<std::string> textureNames;
	textureNames.push_back("64x64.png");
	textureNames.push_back("test.png");
	Textures textures(textureNames,"res/");
	//Get the objects from the level.
	std::vector<Object*>& objects = level.GetObjects();
	Rasterizer rasterizer = Rasterizer(&pixels,textures,level);

	unsigned int currentTime = SDL_GetTicks();
	unsigned int lastTime = SDL_GetTicks();
	float deltaTime = currentTime - lastTime;

	Camera camera(70.0f,(float)(pixels.GetWidth()/pixels.GetHeight()),0.1f,1000.0f,&deltaTime);
	SDL_ShowCursor(0);

	const float HALF_WIDTH = (float)(WIDTH/2);
	const float HALF_HEIGHT = (float)(HEIGHT/2);

	while (!quit)
	{
		currentTime = SDL_GetTicks();	
		SDL_UpdateTexture(window.GetTexture(), NULL ,pixels.GetPixels(),WIDTH * sizeof(Uint32));	
		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering
		pixels.Clear(128);	
		
		//1.Events
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = true;
			}
			SDL_WarpMouseInWindow(window.GetWindow(),(int)HALF_WIDTH,(int)HALF_HEIGHT);
			camera.UpdateCamera(&event,HALF_WIDTH,HALF_HEIGHT);
		}
		//2.Logic
		//3.Rendering
	        SDL_RenderClear(window.GetRenderer());
		SDL_RenderCopy(window.GetRenderer(), window.GetTexture(), NULL, NULL);
	        SDL_RenderPresent(window.GetRenderer());
       		for(unsigned int i = 0;i < objects.size();i++)
		{
			rasterizer.RasterizeObjMesh(camera.GetMatrix(),objects.at(i));
		}
		rasterizer.ClearZBuffer();
		deltaTime = (float)((currentTime - lastTime)/1000.0f);
		lastTime = currentTime;
		
	}

	window.destroy(); 
	SDL_Quit(); 
	return 0;
}
