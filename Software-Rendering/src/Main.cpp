#include <iostream>
#include "HeadersInclude.h"
//Temporary include calls
#include <time.h>
#include <math.h>
#include <chrono> // This might not be a good choice since it might not be supported across all compilers.
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
	LevelLoader_Obj level("level0.obj");	
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
	Matrix4f projection = Matrix4f().InitializeIdentity().PerspectiveProjection(70,pixels.GetWidth()/pixels.GetHeight(),0.1,1000);
	Matrix4f translation = Matrix4f().InitializeIdentity().Translate(Vector3f(0,0,3));
	projection = projection * translation;
	//// End of Temporary Variables ///
	
	//Used for delta counter.
	auto lastTime = std::chrono::high_resolution_clock::now();
	float rotationSpeed = 20;
	float horizontalRotAmount = 0.0;
	float verticalRotAmount = 0.0;
	while (!quit)
	{	
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto delta = (std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime-lastTime).count())/1000000;
		lastTime = currentTime;
		
		SDL_UpdateTexture(window.GetTexture(), NULL ,pixels.GetPixels(),WIDTH * sizeof(Uint32));	
		//Logic of this loop
		//------------------
		//1.Events
		//2.Logic
		//3.Rendering
		//Just some test code for the triangle rasterization.		
		Matrix4f rotation = Matrix4f().InitializeIdentity().RotateAroundY(horizontalRotAmount * 0.09).RotateAroundX(verticalRotAmount * 0.09);
		rotation = projection * rotation;
		
		pixels.Clear(128);		

		rasterizer.RasterizeObjMesh(&rotation,objects.at(0));
		//rotAmount = rotAmount + delta;
		//End of test code.
		//1.Events
		while(SDL_PollEvent(&event))
		{
			if( event.type == SDL_QUIT )
			{ 
			quit = true;																					
			}
			if (event.type == SDL_KEYDOWN)
    			{
				if (event.key.keysym.sym == SDLK_LEFT)
        			{
					horizontalRotAmount = horizontalRotAmount + rotationSpeed;
					std::cout << "Left Arrow " << horizontalRotAmount << std::endl;
				}
				if (event.key.keysym.sym == SDLK_RIGHT)
        			{
					horizontalRotAmount = horizontalRotAmount + -rotationSpeed;
					std::cout << "Right Arrow " << horizontalRotAmount << std::endl;
				}
				if (event.key.keysym.sym == SDLK_UP)
        			{
					verticalRotAmount = verticalRotAmount + rotationSpeed;
					std::cout << "Up Arrow " << verticalRotAmount << std::endl;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
        			{
					verticalRotAmount = verticalRotAmount + -rotationSpeed;
					std::cout << "Down Arrow " << verticalRotAmount << std::endl;
				}
				if (event.key.keysym.sym == SDLK_r)
        			{
					verticalRotAmount = 0;
					horizontalRotAmount = 0;
				}
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
