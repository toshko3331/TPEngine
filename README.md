TPEngine
========
At the moment this project is aimed at creating a game engine + a game with that engine. The goal for this project is to be submitted to the National STEM Video Game Challenge. Although I have a pretty tight budget,timewise at least, I believe I will be able to accomplish this goal. The engine will be written in C++ and will be cross-platform (hopefully). This project uses CMake for building the Windows 7 project and a plain Makefile for the Linux build. The reason for this is because of my ignorance of how CMake works and although it's entire point is to make everything platform independent, I simply don't have the time to spare to fix this part of the project. If there is time left over, I will make everything as platform independent as possible.


* <h2>Libraries </h2>
  * <h5>SDL2 - This is the best library for making a platform independant game. Provides me with an easy way to handle creating windows and figuring out all of the OS dependant rendering code.</h5>

* <h2>Known Problems/Improvments to be made</h2>
  * <h5>Take full of advantage of CMake and make the code run with just the CMake and not have to manually create the Makefile.
