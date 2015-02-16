#include "HeadersInclude.h"

void OBJLevel::AppendVertex(std::string source)
{
	//Doing it 3 times for each vertex.
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		//Getting the vertex and storing it in the vertex vector.    
		m_vertecies.push_back(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next vertex.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void OBJLevel::AppendTexel(std::string source)
{
	//Loop 2 times. Once for each texel.
	for(int i = 0; i < 2;i++)
	{
		//Finding out the boundaries of the texel in the text.
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		//Getting the texels and storing them in the texel vector.    
		m_texelCoords.push_back((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str()));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void OBJLevel::AppendNormal(std::string source)
{
	//Doing it 3 times for each normal coordinate.
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		//Getting the normal and storing it in the normal vector.    
		m_normals.push_back(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next vertex.
		source = source.erase(0,secondDelimiterLocation);
	}	
}

void OBJLevel::AppendFace(Object* object,std::string source)
{
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);
		int firstSlashDelimiterLocation = source.find_first_of('/');
		int secondSlashDelimiterLocation = source.find_first_of('/',firstSlashDelimiterLocation+1);
		//Getting the faces and storing them in the face vector.
		//Minusing when we have the number as an int because the obj file starts to count at 1 and not 0 as we need it.
		object->AddFace((atoi((source.substr(firstDelimiterLocation + 1,firstSlashDelimiterLocation - firstDelimiterLocation - 1)).c_str())) - 1);
		object->AddFace((atoi((source.substr(firstSlashDelimiterLocation + 1,secondDelimiterLocation - firstSlashDelimiterLocation - 1)).c_str())) - 1);
		if(i != 2)
		{
			object->AddFace((atoi((source.substr(secondSlashDelimiterLocation + 1,secondDelimiterLocation - secondSlashDelimiterLocation)).c_str())) - 1);
		}
		else
		{
			object->AddFace(atoi(source.substr(secondSlashDelimiterLocation + 1,source.find('\n') - 1).c_str()) - 1);
		}
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	
	}
}

std::string OBJLevel::GetNextLine(std::ifstream& mapFile,std::string line)
{
	//By using this method, we can support comments in the fileformat. We also skip 's' because we are not using smoothing.
	do{
		//std::cout << line << std::endl;
		getline(mapFile,line);
	}while(line.compare(0,1,"s",0,1) == 0 || line.compare(0,1,"#",0,1) == 0);
	
	return line;
}

OBJLevel::OBJLevel(std::string objFile)
{
	std::string line;
	std::ifstream mapFile;
	std::string name;
	bool firstPass = true;
	//Opening the file for reading.
	mapFile.open(objFile.c_str(),std::fstream::in);
	
	//TODO:Add a field whcich reads the texture used for the file.
	if(mapFile.is_open())
	{
		while (getline(mapFile,line))
		{
			
			
			//Initial check since getline() doesnt do a check.
			if(line.compare(0,1,"s",0,1) == 0 || line.compare(0,1,"#",0,1) == 0)
			{
				line = GetNextLine(mapFile,line);
				//std::cout << "I entered here" << std::endl;
			}
			
			Object object;
			
			if(firstPass)
			{
				if(line.compare(0,1,"o",0,1) == 0)
				{
					//Set object's  'name' to that of the parmater in 'o'.
					object.SetObjectName(line.substr(2));
					line = GetNextLine(mapFile,line);
					firstPass = false;
				}
			}else
			{
				//Set object's 'name'.
				object.SetObjectName(name);
			}
			
			//std::cout << line << std::endl;
			if(line.compare(0,2,"v ",0,2) == 0)
			{
				
				while(line.compare(0,2,"v ",0,2) == 0)
				{
					//Set object's vertecies to that of the parmater in 'v'.
					AppendVertex(line);	
					line = GetNextLine(mapFile,line);
				}
			}
			
			if(line.compare(0,2,"vt",0,2) == 0)
			{
				//Set object's texel to that of the parmater in 'vt'.
				while(line.compare(0,2,"vt",0,2) == 0)
				{
					//Set object's vertecies to that of the parmater in 'v'.
					AppendTexel(line);
					line = GetNextLine(mapFile,line);
				}	
				//std::cout << object.GetRawVertexVector().at(0) << std::endl; 
			}
			if(line.compare(0,2,"vn",0,2) == 0)
			{
				while(line.compare(0,2,"vn",0,2) == 0)
				{
					//Set object's normals to that of the paramater in 'vn'.
					AppendNormal(line);
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
			if(object.GetObjectName() != "" && m_vertecies.size() != 0 && object.GetFaceVector().size() != 0 && m_texelCoords.size() != 0)
			{
				objectVector.push_back(object);
				//Basically a saftey check for EOF.
				if(line != "")
				{
					name = line.substr(2);
				}
			}
		}
	}else
	{
		ErrorReport::WriteToLog("Could not open .obj file.");
		exit(EXIT_FAILURE);
		
	}
	mapFile.close();
}
