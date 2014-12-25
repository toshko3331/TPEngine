#include <iostream>
#include "HeadersInclude.h"

Bitmap::Bitmap(int width,int height) : m_width(width), 	m_height(height)
{
	//Since we are using 4 byte data types to store our pixels instead of my initial thought of usinc chars
	//We don't have to do (width * height * 4) for our array decleration.
	m_pixels = new Uint32[width * height];
	Bitmap::Clear(128);
}

Bitmap::~Bitmap(){
	//Clearing memory.
	delete[] m_pixels;
}

void  Bitmap::Clear(Uint32 shade)
{
	//Probably fastest way to set the pixels to a certain value.
	memset(m_pixels,shade, m_width * m_height * sizeof(Uint32) );
}

void Bitmap::SetPixel(int x,int y,Uint32 a,Uint32 r,Uint32 g,Uint32 b)
{
	//Bitshifting colors into the correct positions for the ARGB format.
	m_pixels[y * m_width + x] = b | (g << 8) | (r << 16) | (a << 24);
}
