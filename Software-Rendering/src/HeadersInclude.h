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
#include "png.h"
#include "Vector4f.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "ErrorReport.h"
#include "Matrix4f.h"
#include "Window.h"
#include "Bitmap.h"
#include "Vertex.h"
#include "Camera.h"
#include "Gradients.h"
#include "Edge.h"
#include "Object.h"
#include "OBJLevel.h"
#include "Textures.h"
#include "Rasterizer.h"
#endif
