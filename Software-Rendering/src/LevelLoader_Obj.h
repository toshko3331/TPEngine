#pragma once
#include "HeadersInclude.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

class LevelLoader_Obj
{
	public:
		LevelLoader_Obj(std::string filename);
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		std::vector<Object>& GetObjects(){ return objectVector; } 
	private:
		void AppendVertex(Object* object, std::string source);
		void AppendFace(Object* object, std::string source);
		void AppendTexel(Object* object, std::string source);
		std::vector<Object> objectVector;	
};
