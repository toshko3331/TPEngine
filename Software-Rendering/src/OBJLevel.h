#pragma once
#include "HeadersInclude.h"
#include <fstream>
#include <string>
#include <vector>

class OBJLevel
{
	public:
		OBJLevel(std::string filename);
		~OBJLevel();
	 	std::vector<Object*>& GetObjects(){ return m_objectVector; }

		const std::vector<float>& GetVertecies()  { return m_vertecies; }
		const std::vector<float>& GetTexelVector() { return m_texelCoords; }
		const std::vector<float>& GetNormals() { return m_normals; }
	private:
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		void AppendVertex(std::string source);
		void AppendFace(Object* object, std::string source);
		void AppendTexel(std::string source);
		void AppendNormal(std::string source);
		void AssignTexture(Object* object,const std::string materialName);	
		std::vector<Object*> m_objectVector;

		std::vector<float> m_vertecies;
		std::vector<float> m_texelCoords;
		std::vector<float> m_normals;
		std::ifstream m_MTLFile;
};
