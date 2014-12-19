cmake_minimum_required(VERSION 3.1)
PROJECT(SoftwareRendering)

#Constructor of file we are using has the paramaters of: GLOB_RECURSE <varnames> <NamesOfFiles>
#GLOB_RECURSE sets the variable (for example HDRS) equal to the entire list of file names that are given.
#Easiest way to get this data, used later for building the project. '*' wildcard character is used to iteriate through all the files :P
file(GLOB_RECURSE HDRS ${SoftwareRendering_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SRCS
	${SoftwareRendering_SOURCE_DIR}/src/*.cpp
	${SoftwareRendering_SOURCE_DIR}/src/*.c
)
#Including the directories of SDL2
include_directories( ${SoftwareRendering_SOURCE_DIR}/lib/SDL2/include/)
#Setting a variable for easier use
SET(ALLFILES ${HDRS} ${SRCS} )
#Actually building the project
add_executable(SoftwareRendering ${ALLFILES} )
#Linking the project with the static libraries
target_link_libraries(SoftwareRendering 
	
	${SoftwareRendering_SOURCE_DIR}/lib/SDL2/x86/SDL2main.lib
	${SoftwareRendering_SOURCE_DIR}/lib/SDL2/x86/SDL2.lib
	
	)
	