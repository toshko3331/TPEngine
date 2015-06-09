#include "HeadersInclude.h"
#include <dirent.h>

Textures::Textures(std::string filePath)
{
	LoadTexturesFromPath(filePath);
}

Textures::~Textures()
{
	for(unsigned int i = 0; i < m_textureBitmaps.size();i++)
	{
		delete m_textureBitmaps.at(i);
	}
}

Bitmap* Textures::GetTextureByName(std::string name)
{
	for(unsigned int i = 0;i < m_textureBitmaps.size();i++)
	{
		if(name == m_textureNames.at(i))
		{
			return m_textureBitmaps.at(i);
		}
	}
	//TODO:Return an error texture, this way we don't have to crash the program (i.e. the source engine's red "ERROR" texture).
	ErrorReport::WriteToLog("No texture found in texture array.");
	exit(EXIT_FAILURE);
}

void Textures::LoadTexturesFromPath(std::string filePath)
{
	
	struct dirent* readData = NULL;
        DIR* directory = opendir(filePath.c_str());
        while((readData = readdir(directory)) != NULL)
        {
                std::string filename = readData->d_name;
                unsigned int numCharsUntilDot = filename.find_last_of('.');
                if(numCharsUntilDot == std::string::npos) // no '.' found
                {
                        continue;
                }
                if(filename.find(EXSTENSION,numCharsUntilDot) != std::string::npos && EXSTENSION.length() + numCharsUntilDot + 1 == filename.length())
                {
                	std::string name = filePath + filename;
			m_textureBitmaps.push_back(new Bitmap(name));
			m_textureNames.push_back(name);
			continue;
                }
        }
        closedir(directory);
}

	
