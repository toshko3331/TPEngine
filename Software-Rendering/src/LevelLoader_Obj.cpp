#include "HeadersInclude.h"

void LevelLoader_Obj::AppendFace(Object* object,std::string source)
{
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);
		int slashDelimiterLocation = source.find_first_of('/');
		//Getting the faces and storing them in the face vector.
		//Minusing when we have the number as an int because the obj file starts to count at 1 and not 0 as we need it.
		object->AddFace((atoi((source.substr(firstDelimiterLocation + 1,slashDelimiterLocation - firstDelimiterLocation - 1)).c_str())) - 1);
		if(i != 2)
		{
			object->AddFace((atoi((source.substr(slashDelimiterLocation + 1,slashDelimiterLocation - secondDelimiterLocation)).c_str())) - 1);
		}
		else
		{
			object->AddFace(atoi(source.substr(slashDelimiterLocation + 1,source.find('\n') - 1).c_str()) - 1);
		}
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	
	}
}

void LevelLoader_Obj::AppendTexel(Object* object, std::string source)
{
	//Loop 2 times. Once for each texel.
	for(int i = 0; i < 2;i++)
	{
		//Finding out the boundaries of the texel in the text.
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		//Getting the texels and storing them in the texel vector.    
		object->AddTexel((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str()));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void LevelLoader_Obj::AppendVertex(Object *object,std::string source)
{
	//Doing it 3 times for each vertex.
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		//Getting the vertex and storing it in the vertex vector.    
		object->AddVertex(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next vertex.
		source = source.erase(0,secondDelimiterLocation);
	}	
}

std::string LevelLoader_Obj::GetNextLine(std::ifstream& mapFile,std::string line)
{
	//By using this method, we can support comments in the fileformat. We also skip 's' because we are not using smoothing.
	do{
		getline(mapFile,line);
	}while(line.compare(0,1,"#",0,1) == 0 || line.compare(0,1,"s",0,1) == 0  );
	return line;
}

LevelLoader_Obj::LevelLoader_Obj(std::string objFile)
{
	std::string line;
	std::ifstream mapFile;
	//Opening the file for reading.
	mapFile.open(objFile.c_str(),std::fstream::in);
	
	//TODO:Add a field whcich reads the texture used for the file.
	if(mapFile.is_open())
	{
		while (getline(mapFile,line))
		{
			Object object;
			if(line.compare(0,1,"o",0,1) == 0)
			{
				//Set object's  'name' to that of the parmater in 'o'.
				object.SetObjectName(line.substr(2));
				line = GetNextLine(mapFile,line);
			}
			if(line.compare(0,2,"v ",0,2) == 0)
			{
				while(line.compare(0,2,"v ",0,2) == 0)
				{
					//Set object's vertecies to that of the parmater in 'v'.
					AppendVertex(&object,line);	
					line = GetNextLine(mapFile,line);
				}
			}
			if(line.compare(0,2,"vt",0,2) == 0)
			{
				//Set object's texel to that of the parmater in 'vt'.
				while(line.compare(0,2,"vt",0,2) == 0)
				{
					//Set object's vertecies to that of the parmater in 'v'.
					AppendTexel(&object,line);
					line = GetNextLine(mapFile,line);
				}	
			}
			if(line.compare(0,1,"f",0,1) == 0)
			{
				//Set object's face coordinates to the acoording coordinates.
				while(line.compare(0,1,"f",0,1) == 0)
				{
					//Set object's vertecies to that of the parmater in 'v'.
					AppendFace(&object,line);
					line = GetNextLine(mapFile,line);
				}
			}
			//Checking agianst intializing an empty object.
			if(object.GetRawVertexVector().size() != 0 && object.GetFaceVector().size() != 0 && object.GetTexelVector().size() != 0)
			{
				objectVector.push_back(object);
			}	
		}
	}else
	{
		//TODO:Add an error reporter log here.
		std::cout << "FATAL ERROR:Could not open .obj file." << std::endl;
	}
}
