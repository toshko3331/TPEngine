#pragma once
#include "HeadersInclude.h"


class Bitmap
{
	public:
		Bitmap(int width,int height);
		Bitmap(std::string filePath);
		~Bitmap();
		void Clear(Uint32 shade);
		void SetPixel(int x,int y,Uint32 a,Uint32 r,Uint32 g,Uint32 b);
		void CopyTexelToPixel(int texelXCoord,int texelYCoord,int pixelXCoord,int pixelYCoord,Bitmap* texture);
		int GetPixel(int location){ return m_pixels[location]; } 
		int GetWidth() { return m_width;}
		int GetHeight() { return m_height;}
		Uint32* GetPixels(){ return m_pixels; } 
	private:
		static int GetImageDimension(std::string filePath,bool getWidth);
		int m_width;
		int m_height;
		Uint32* m_pixels;
};
