#include <iostream>
#include "HeadersInclude.h"

Bitmap::Bitmap(int width,int height) : m_width(width), 	m_height(height)
{
	//Since we are using 4 byte data types to store our pixels instead of my initial thought of usinc chars
	//We don't have to do (width * height * 4) for our array decleration.
	m_pixels = new Uint32[width * height];
	Bitmap::Clear(128);
}

Bitmap::Bitmap(std::string filePath) : m_width(GetImageDimension(filePath,true)), m_height(GetImageDimension(filePath,false))
{	
	unsigned char pngSigniture[8];
	//Opening the file in binary reading mode.
	FILE* texture = fopen(filePath.c_str(), "rb");
	if(!texture)
	{
		ErrorReport::WriteToLog(filePath.append(" failed to be loaded."));
		return;
	}
	fread(pngSigniture,1,8,texture);
	//Checking if the file is of type PNG.
	if(png_sig_cmp(pngSigniture,0,8))
	{
		ErrorReport::WriteToLog(filePath.append(" is not a PNG type file."));
		return;
	}
	//Intialize the first struct.
	png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	if(pngReadStruct == NULL)
	{
		ErrorReport::WriteToLog(std::string("Read structure for ").append(filePath).append(" was not initalized correctly."));
		return;
	}
	//Intialize the second struct.
	png_infop pngInfoStruct = png_create_info_struct(pngReadStruct);
	if(pngInfoStruct == NULL)
	{
		ErrorReport::WriteToLog(std::string("Info structure for ").append(filePath).append(" was not initalized correctly."));
		return;
	}
	//Any I/O problem call this.
	if(setjmp(png_jmpbuf(pngReadStruct)))
	{
		ErrorReport::WriteToLog(std::string("Error during I/O of file ").append(filePath));
		return;
	}
	//Initalizing standard C I/O stream
	png_init_io(pngReadStruct,texture);
	//Sets the amount of bytes to be read as the signature.
	png_set_sig_bytes(pngReadStruct,8);
	//Reading information before we get to the good stuff, the image data.
	png_read_info(pngReadStruct,pngInfoStruct);
	
	//Allocating the space needed to store the pixels.
	m_pixels = new Uint32[m_width * m_height];

	//Checking if the image was changed in any way since we started reading.
	png_read_update_info(pngReadStruct,pngInfoStruct);
	
	//We malloc(allocate) all of the necessarry memory for the texture.
	png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * m_height);
	for(int y = 0; y < m_height; y++)
	{
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(pngReadStruct,pngInfoStruct));
	}
	
	//Read the image into our 2 dimensional array.
	png_read_image(pngReadStruct, row_pointers);

        for (int y = 0;y < m_height; y++) 
	{
		int j = 0;
                for (int x = 0;x < m_width * 4;x+=4)
		{	
			//Bit shifting according to our ARGB format. Since the image is stored as RGBA, we need to get the 4th element first (the alpha) because we are using ARGB. 
			//This is why it might look slightly out of order.
			m_pixels[y * m_width + j] =  (int)row_pointers[y][x + 3] << 24  | (int)row_pointers[y][x + 0] << 16 | (int)row_pointers[y][x + 1] << 8 | (int)row_pointers[y][x + 2] << 0;
			j++;
                }
        }

	//Make sure to always clean up malloc
        for (int i = 0;i < m_height; i++)
	{
                free(row_pointers[i]);
	}        
	free(row_pointers);
	fclose(texture);
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

void Bitmap::CopyTexelToPixel(int texelXCoord,int texelYCoord,int pixelXCoord,int pixelYCoord,Bitmap* texture)
{
	m_pixels[pixelYCoord * m_width + pixelXCoord] = texture->GetPixel((texelYCoord * texture->GetWidth()) + texelXCoord);
}

//Static member function to get the dimensions of the image.
int Bitmap::GetImageDimension(std::string filePath,bool getWidth)
{
	/* For commented version, refer to the texture constructor. */
	unsigned char pngSigniture[8];
	FILE* texture = fopen(filePath.c_str(), "rb");
	if(!texture)
	{
		ErrorReport::WriteToLog(filePath.append(" failed to be loaded during dimension gathering."));
		return -1;
	}
	fread(pngSigniture,1,8,texture);
	if(png_sig_cmp(pngSigniture,0,8))
	{
		ErrorReport::WriteToLog(filePath.append(" is was not recognized as a PNG during dimension gathering."));
		return -1;
	}
	if(!texture)
	{
		ErrorReport::WriteToLog(filePath.append(" failed to be loaded during dimension gathering."));
		return -1;
	}
	png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	if(pngReadStruct == NULL)
	{
		ErrorReport::WriteToLog(std::string("Read structure for ").append(filePath).append(" during dimension gathering was not initalized correctly."));
		return -1;
	}
	png_infop pngInfoStruct = png_create_info_struct(pngReadStruct);
	if(pngInfoStruct == NULL)
	{
		ErrorReport::WriteToLog(std::string("Info structure for ").append(filePath).append(" during dimension gathering was not initalized correctly."));
		return -1;
	}
	if(setjmp(png_jmpbuf(pngReadStruct)))
	{
		ErrorReport::WriteToLog(std::string("Error during I/O of file ").append(filePath).append(" during dimension gathering."));
		return -1;
	}
	png_init_io(pngReadStruct,texture);
	png_set_sig_bytes(pngReadStruct,8);
	png_read_info(pngReadStruct,pngInfoStruct);
	if(getWidth == true)
	{
		int width = png_get_image_height(pngReadStruct,pngInfoStruct);
		fclose(texture);
		return width;
	}else
	{
		int height = png_get_image_height(pngReadStruct,pngInfoStruct);
		fclose(texture);
		return height;
	}
}


