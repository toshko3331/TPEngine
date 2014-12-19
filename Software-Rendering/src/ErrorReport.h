#pragma once
#include <fstream>
#include <string>
#include <SDL\SDL.h>
class ErrorReport
{
public:
	static void WriteToLog(std::string error)
	{
		std::ofstream log;
		log.open("ErrorLog.txt");
		log << error << " error: " << SDL_GetError() << std::endl;
		log.close();
	}
};

