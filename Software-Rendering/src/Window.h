#pragma once
#include "HeadersInclude.h"
#include <string>


class Window
{

	public:
		Window(const char* title,int x,int y,int width, int height,Uint32 flags);
		void destroy();
		//Getters
		SDL_Window* GetWindow() {return m_window; }
		SDL_Renderer* GetRenderer() {return m_renderer;}
		SDL_Texture* GetTexture() {return m_texture;}

		int GetWindowWidth()	{ return m_windowWidth; }
		int GetWindowHeight()	{ return m_windowHeight; } 
		/////
	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;

		int m_windowWidth;
		int m_windowHeight;
};
