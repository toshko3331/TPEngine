BUILD_DIR = build/
CXX = g++
OUT = $(BUILD_DIR)Engine
CFLAGS = -g -Wall

#Directory to source files
SRC = $(shell pwd)/Software-Rendering/src/
H = $(SRC)Bitmap.h $(SRC)ErrorReport.h $(SRC)Vector3f.h $(SRC)Window.h $(SRC)Vector4f.h $(SRC)Vertex.h $(SRC)Rasterizer.h $(SRC)Vector2f.h $(SRC)Edge.h $(SRC)Matrix4f.h
CPP = $(SRC)Bitmap.cpp $(SRC)ErrorReport.cpp $(SRC)Vector3f.cpp $(SRC)Window.cpp $(SRC)Vector4f.cpp $(SRC)Vertex.cpp $(SRC)Rasterizer.cpp $(SRC)Main.cpp $(SRC)Edge.cpp $(SRC)Matrix4f.cpp
#Directory to include
INCLUDE = $(shell sdl2-config --cflags)
#Linking Directories
LDFLAGS = $(shell sdl2-config --libs)

OBJECTS = $(BUILD_DIR)Main.o $(BUILD_DIR)Bitmap.o $(BUILD_DIR)Vector3f.o $(BUILD_DIR)Window.o $(BUILD_DIR)Vector4f.o $(BUILD_DIR)Vertex.o $(BUILD_DIR)Rasterizer.o $(BUILD_DIR)Edge.o $(BUILD_DIR)Vector2f.o $(BUILD_DIR)Matrix4f.o


all:$(OUT)
#Linking all the files.
$(OUT):$(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CFLAGS)

#Creating all object files below.
$(BUILD_DIR)Main.o:$(SRC)Main.cpp
	$(CXX) -c $(SRC)Main.cpp $(INCLUDE) -o $(BUILD_DIR)Main.o 

$(BUILD_DIR)Vector3f.o:$(SRC)Vector3f.cpp $(SRC)Vector3f.h
	$(CXX) -c $(SRC)Vector3f.cpp $(INCLUDE) -o $(BUILD_DIR)Vector3f.o 

$(BUILD_DIR)Bitmap.o:$(SRC)Bitmap.cpp $(SRC)Bitmap.h
	$(CXX) -c $(SRC)Bitmap.cpp $(INCLUDE) -o $(BUILD_DIR)Bitmap.o 

$(BUILD_DIR)Window.o:$(SRC)Window.cpp $(SRC)Window.h
	$(CXX) -c $(SRC)Window.cpp $(INCLUDE) -o $(BUILD_DIR)Window.o 

$(BUILD_DIR)Vector4f.o:$(SRC)Vector4f.cpp $(SRC)Vector4f.h
	$(CXX) -c $(SRC)Vector4f.cpp $(INCLUDE) -o $(BUILD_DIR)Vector4f.o 

$(BUILD_DIR)Vertex.o:$(SRC)Vertex.cpp $(SRC)Vertex.h
	$(CXX) -c $(SRC)Vertex.cpp $(INCLUDE) -o $(BUILD_DIR)Vertex.o

$(BUILD_DIR)Edge.o:$(SRC)Edge.cpp $(SRC)Edge.h
	$(CXX) -c $(SRC)Edge.cpp $(INCLUDE) -o $(BUILD_DIR)Edge.o

$(BUILD_DIR)Rasterizer.o:$(SRC)Rasterizer.cpp $(SRC)Rasterizer.h
	$(CXX) -c $(SRC)Rasterizer.cpp $(INCLUDE) -o $(BUILD_DIR)Rasterizer.o

$(BUILD_DIR)Vector2f.o:$(SRC)Vector2f.cpp $(SRC)Vector2f.h
	$(CXX) -c $(SRC)Vector2f.cpp $(INCLUDE) -o $(BUILD_DIR)Vector2f.o

$(BUILD_DIR)Matrix4f.o:$(SRC)Matrix4f.cpp $(SRC)Matrix4f.h
	$(CXX) -c $(SRC)Matrix4f.cpp $(INCLUDE) -o $(BUILD_DIR)Matrix4f.o


#All of the clean up stuff below
clean:
	rm -f $(OUT) $(OBJECTS)
clean_obj:
	rm -f $(OBJECTS)
