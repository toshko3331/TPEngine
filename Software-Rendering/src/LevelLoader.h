#pragma once
#include "HeadersInclude.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>


class LevelLoader
{

	public:
		LevelLoader(std::string filename);
		std::vector<Object>& GetObjects(){return m_objects; }
	private:
		void AppendVertex(Object* object, std::string source,int currentIndex);
		void AppendFaces(Object* object, std::string source,int currentIndex);
		void AppendTexel(Object* object, std::string source,int currentIndex);
		void AddWorldLocationToObject(std::string line,Object* object);
		void AddEulerRotationToObject(std::string line,Object* object);
		void AddScaleToObject(std::string line,Object* object);
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		std::vector<Object> m_objects;
};

