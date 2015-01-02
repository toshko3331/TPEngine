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
		ErrorReport::WriteToLog("SDL_Init");
		return 1;
	}
		
	Window window = Window("Software Renderer",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

	Bitmap pixels = Bitmap(window.GetWindowWidth(),window.GetWindowHeight());
	bool quit = false;
	SDL_Event event;
	//// Temporary Variables for Testing Code  ///	
	Vertex v1 = Vertex(Vector4f(0,1,0,1),
			Vector2f(0.5,1));
	Vertex v2 = Vertex(Vector4f(-1,-1,0,1),
			Vector2f(0,0));
	Vertex v3 = Vertex(Vector4f(1,-1,0,1),
			Vector2f(1,0));
	srand(time(NULL));
	
	Rasterizer rasterizer = Rasterizer(&pixels);
	Matrix4f projection = Matrix4f().InitializeIdentity().PerspectiveProjection(70,pixels.GetWidth()/pixels.GetHeight(),0.1,1000);
	Matrix4f translation = Matrix4f().InitializeIdentity().Translate(Vector3f(0,0,3));
	projection = projection * translation;
	//// End of Temporary Variables ///
	
	//Used for delta counter.
	auto lastTime = std::chrono::high_resolution_clock::now();
	float rotAmount = 0.0;
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
		///	v1 = Vertex(Vector4f(rand()%WIDTH,rand()%HEIGHT,0,0));
		///	v2 = Vertex(Vector4f(rand()%WIDTH,rand()%HEIGHT,0,0));
		///	v3 = Vertex(Vector4f(rand()%WIDTH,rand()%HEIGHT,0,0));
				
		Matrix4f rotation = Matrix4f().InitializeIdentity().RotateAroundY(rotAmount * 0.09);
		rotation = projection * rotation;
		
		pixels.Clear(128);		
		
		rasterizer.RasterizeTriangle(v1.ApplyTransformations(rotation),v2.ApplyTransformations(rotation),v3.ApplyTransformations(rotation));
	
		rotAmount = rotAmount + delta;
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
