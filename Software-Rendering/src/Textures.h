#include "HeadersInclude.h"
#include <string>
#include <vector>

class Textures{

	public:
		Textures(std::string filePath = std::string("."));
		~Textures();		
		Bitmap* GetTextureByName(std::string name);
		std::vector<Bitmap*>& GetTextures(){ return m_textureBitmaps; }
	private:
		std::vector<Bitmap*> m_textureBitmaps;
		std::vector<std::string> m_textureNames;
		std::string EXSTENSION = "png";
		void LoadTexturesFromPath(std::string filePath);
};
