#pragma once
#include "HeadersInclude.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>


class LevelLoader_TPMap
{

	public:
		LevelLoader_TPMap(std::string filename);
		std::vector<Object>& GetObjects(){return m_objects; }
	private:
		void AppendVertex(Object* object, std::string source);
		void AppendFaces(Object* object, std::string source);
		void AppendTexel(Object* object, std::string source);
		void AddWorldLocationToObject(std::string line,Object* object);
		void AddEulerRotationToObject(std::string line,Object* object);
		void AddScaleToObject(std::string line,Object* object);
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		std::vector<Object> m_objects;
};

