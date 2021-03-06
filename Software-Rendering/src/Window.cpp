#include <string>
#include "HeadersInclude.h" 

Window::Window(const char* title,int x,int y,int width, int height,Uint32 flags) : m_windowWidth(width), m_windowHeight(height)
{
	////////////////////////////////Basic intialziation stuff, sets up a window, then a renderer and a texture so it can be drawn on.////////////////////////////////////
   //Creates the actual widndow

	m_window = SDL_CreateWindow(title, x, y, width, height,flags);
	//Error Checking Code.
	if(m_window == NULL)
	{
		ErrorReport::WriteToLog_SDL("SDL_CreateWindow");
		SDL_Quit();
	}

	//Creates renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
	//Error Checking Code.	
        if(m_renderer == NULL)
	{
		ErrorReport::WriteToLog_SDL("SDL_CreateRenderer");
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
	
	//Creates Texture with with 8 bit ARGB format.
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, m_windowWidth, m_windowHeight);
   	//Error Checking Code.
	if(m_texture == NULL)
	{
		ErrorReport::WriteToLog_SDL("SDL_CreateWindow");
		
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
	}

}

void Window::destroy()
{
	//Properly dispose of everything that we have intialized.
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}


