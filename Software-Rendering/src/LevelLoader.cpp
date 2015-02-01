#include "HeadersInclude.h"

void LevelLoader::appendVertex(Object* object, std::string source,int currentIndex)
{
	//Doing it 4 times for each vertex.
	for(int i = 0; i < 4;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of('/');
		int secondDelimiterLocation = source.find_first_of('/',firstDelimiterLocation+1);

		//Getting the vertex and storing it in the vertex vector.    
		object->AddVertex(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next vertex.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void LevelLoader::appendFaces(Object* object, std::string source,int currentIndex)
{
	//Doing it 3 times for each face since our algorithm can only draw in triagnles.
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of('/');
		int secondDelimiterLocation = source.find_first_of('/',firstDelimiterLocation+1);

		//Getting the face and storing it in the vertex vector.    
		object->AddFace(atoi((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str()));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void LevelLoader::appendTexel(Object* object, std::string source,int currentIndex)
{
	//Doing it 3 times for each face since our algorithm can only draw in triagnles.
	for(int i = 0; i < 3;i++)
	{
		//Finding out the boundaries of the nubmer
		int firstDelimiterLocation = source.find_first_of('/');
		int secondDelimiterLocation = source.find_first_of('/',firstDelimiterLocation+1);

		//Getting the face and storing it in the vertex vector.    
		object->AddTexel((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str()));
		//Since this string is local, we simply erase it, and this way we dont have to compute any text postion data for the next face.
		source = source.erase(0,secondDelimiterLocation);
	}
}

void LevelLoader::AddWorldLocationToObject(std::string line,Object* object)
{
	float x,y,z;
	x = y = z = 0;
	//Keeping track of which variables are intialized just incase something happens.
	bool xIsInit = false;
	bool yIsInit = false;
	bool zIsInit = false;
	while((xIsInit == false) && (yIsInit == false) && (zIsInit == false))
	{
		for(int i = 0; i < 3;i++)
		{
			//Finding out the boundaries of the nubmer
			int firstDelimiterLocation = line.find_first_of('/');
			int secondDelimiterLocation = line.find_first_of('/',firstDelimiterLocation+1);

			//We do the calculation for each different coordinate at a different index because it flows nicely with the erase function of the string class.
			if(i == 0 && (xIsInit == false))
			{
				x = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				xIsInit = true;
			}
			if(i == 1 && (yIsInit == false))
			{
				y = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				yIsInit = true;
			}
			if(i == 2 && (zIsInit == false))
			{
				z = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				zIsInit = true;
			}
				
			line = line.erase(0,secondDelimiterLocation);
		}
	}
	//Finally assigning the world position from the read input to the object.
	object->SetWorldPosition(x,y,z);
}

void LevelLoader::AddEulerRotationToObject(std::string line,Object* object)
{
	float x,y,z;
	x = y = z = 0;
	//Keeping track of which variables are intialized incase of some errror occuring. Basically error-checking code.
	bool xIsInit = false;
	bool yIsInit = false;
	bool zIsInit = false;
	while((xIsInit == false) && (yIsInit == false) && (zIsInit == false))
	{
		for(int i = 0; i < 3;i++)
		{
			//Finding out the boundaries of the nubmer
			int firstDelimiterLocation = line.find_first_of('/');
			int secondDelimiterLocation = line.find_first_of('/',firstDelimiterLocation+1);

			//We do the calculation for each different coordinate at a different index because it flows nicely with the erase function of the string class.
			if(i == 0 && (xIsInit == false))
			{
				x = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				xIsInit = true;
			}
			if(i == 1 && (yIsInit == false))
			{
				y = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				yIsInit = true;
			}
			if(i == 2 && (zIsInit == false))
			{
				z = (float)atof((line.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str());
				zIsInit = true;
			}
				
			line = line.erase(0,secondDelimiterLocation);
		}
	}
	//Finally assigning the Euler Rotation from the read input to the object.
	object->SetObjectEulerRotation(x,y,z);
}

std::string LevelLoader::GetNextLine(std::ifstream& mapFile,std::string line)
{
	//By using this method, we can support comments in the fileformat.
	do{
		getline(mapFile,line);
	}while(line.compare(0,1,"#",0,1) == 0 );
	return line;
}

LevelLoader::LevelLoader(std::string filename)
{
	std::string line;
	std::ifstream mapFile;
	//Opening the file for reading.
	mapFile.open(filename.c_str(),std::fstream::in);
	//Booleans for keeping track in which section the file reader is at.
	bool isInWg = false;
	bool isInWgo = false;
	if (mapFile.is_open())
 	{
		while (getline(mapFile,line))
		{
			if(isInWg || line == "openwg")
			{
				isInWg = true;
				if(isInWgo || (line.compare(0,7,"openwgo",0,7) == 0))
				{
					
					isInWgo = true;
					Object object;
					//Opening the world geometry section.
					if(line.compare(0,7,"openwgo",0,7) == 0)
					{
						object.SetObjectName(line.substr(8));
						line = GetNextLine(mapFile,line);
					}
					//Reading and writing the coordinates relative to world space into 'object'. 
					if(line.compare(0,4,"wpos",0,4) == 0)
					{
						AddWorldLocationToObject(line,&object);
						line = GetNextLine(mapFile,line);
					}
					//Reading and writing into 'object' the rotation of the object in euler angles. 
					if(line.compare(0,3,"rot",0,3) == 0)
					{
						AddEulerRotationToObject(line,&object);
						line = GetNextLine(mapFile,line);
					}
					//Opening the vertex section where all of the vertecies of the object will be read and wrtitten to 'object'.
					if(line == "openov")
					{
						line = GetNextLine(mapFile,line);
						int index = 0;
						while(line != "closeov")
						{
							appendVertex(&object, line,index);
							line = GetNextLine(mapFile,line);
							index++;
						}
						line = GetNextLine(mapFile,line);
					}	
					//Opening the face section where all of the faces of the object will be read and wrtitten to 'object'.
					if(line == "openof")
					{
						line = GetNextLine(mapFile,line);
						int index = 0;
						while(line != "closeof")
						{
							appendFaces(&object, line,index);
							line = GetNextLine(mapFile,line);
							index++;
						}
						line = GetNextLine(mapFile,line);
					}
					if(line == "opent")
					{
						line = GetNextLine(mapFile,line);
						int index = 0;
						while(line != "closet")
						{
							appendTexel(&object, line,index);
							line = GetNextLine(mapFile,line);
							index++;
						}
						//We need to sort the UV coordinates because they are not sorted when they are exported out of Blender. The sorting will make it easier to use the UV coordinates.
						//Insertion sort is theoritcally faster, however; it is not implemented correctly.
						object.BubbleSortTexelCoords();	
						line = GetNextLine(mapFile,line);
					}
					//Reading and writing the texture file name into 'object'
					if(line.substr(0,6) == "uv_map")
					{
						object.SetTextureName(line.substr(7));
						line = GetNextLine(mapFile,line);
					}
					//Closing the object section. All code past this will not be realtive to this object.
					if(line == "closewgo")
					{
						m_objects.push_back(object);
						isInWgo = false;
						line = GetNextLine(mapFile,line);
					}
				}
				//Closing the world geometry section. Pretty much ending the file here.
				if(line == "closewg")
				{
					isInWg = false;
				}
			}			
		}
		mapFile.close();
	}
	else
	{
		//TODO:Add an error reporter log here.
		std::cout << "LEVEL WAS NOT LOADED" << std::endl;
	}
}
