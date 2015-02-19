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
		
	Window window = Window("Software Renderer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

	Bitmap pixels = Bitmap(window.GetWindowWidth(),window.GetWindowHeight());
	bool quit = false;
	SDL_Event event;
	//// Temporary Variables for Testing Code  ///	
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
		for(unsigned int i = 0;i < objects.size();i++)
		{
			rasterizer.RasterizeObjMesh(camera.GetMatrix(),objects.at(i));
		}
		rasterizer.ClearZBuffer();
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
	
	window.destroy(); 
	SDL_Quit(); 
	return 0;
}
