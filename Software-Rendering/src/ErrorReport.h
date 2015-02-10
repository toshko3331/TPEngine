#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "HeadersInclude.h"


class ErrorReport
{
public:
	static void WriteToLog_SDL(std::string error)
	{
		std::ofstream log;
		log.open("ErrorLog_SDL.TPEngineLog");
		log << error << " error: " << SDL_GetError() << std::endl;
		std::cout << error << " error: " << SDL_GetError() << std::endl;
		log.close();
	}

	static void WriteToLog(std::string error)
	{
		std::ofstream log;
		log.open("ErrorLog.TPEngineLog");
		log << "Error: " << error << std::endl;
		std::cout << "Error: " << error << std::endl;
		log.close();
	}
};

