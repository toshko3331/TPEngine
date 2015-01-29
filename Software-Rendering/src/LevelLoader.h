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
		const std::vector<Object>& GetObjcets(){return m_objects; }
	private:
		void appendVertex(Object* object, std::string source,int currentIndex);
		void appendFaces(Object* object, std::string source,int currentIndex);
		void AddWorldLocationToObject(std::string line,Object* object);
		void AddEulerRotationToObject(std::string line,Object* object);
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		std::vector<Object> m_objects;
};

