#pragma once
#include "HeadersInclude.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

class OBJLevel
{
	public:
		OBJLevel(std::string filename);
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		std::vector<Object>& GetObjects(){ return objectVector; }

		const std::vector<float>& GetVertecies()  { return m_vertecies; }
		const std::vector<float>& GetTexelVector() { return m_texelCoords; }
		const std::vector<float>& GetNormals() { return m_normals; }
	private:
		void AppendVertex(std::string source);
		void AppendFace(Object* object, std::string source);
		void AppendTexel(std::string source);
		void AppendNormal(std::string source);
	
		std::vector<Object> objectVector;

		std::vector<float> m_vertecies;
		std::vector<float> m_texelCoords;
		std::vector<float> m_normals;
	
};
