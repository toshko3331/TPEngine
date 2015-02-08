#pragma once
#ifndef HEADERS_INCLUDE
#define HEADERS_INCLUDE
#ifndef WIN32
#include "SDL.h"
#endif
#ifdef WIN32
#include <SDL\SDL.h>
#endif
//Doing it this way so we can include everything with just one header file.
#include "Bitmap.h"
#include "ErrorReport.h"
#include "Vector3f.h"
#include "Window.h"
#include "Vector4f.h"
#include "Matrix4f.h"
#include "Vector2f.h"
#include "Vertex.h"
#include "Gradients.h"
#include "Edge.h"
#include "Object.h"
#include "LevelLoader_TPMap.h"
#include "Rasterizer.h"
#include "LevelLoader_Obj.h"
#endif
