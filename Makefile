BUILD_DIR = build/
CXX = g++
OUT = $(BUILD_DIR)Engine
CFLAGS = -g -Wall

#Directory to source files
SRC = $(shell pwd)/Software-Rendering/src/
H = $(SRC)Bitmap.h $(SRC)ErrorReport.h $(SRC)Vector3.h $(SRC)Window.h $(SRC)Vector4f.h
CPP = $(SRC)Bitmap.cpp $(SRC)ErrorReport.cpp $(SRC)Vector3.cpp $(SRC)Window.cpp $(SRC)Vector4f.cpp $(SRC)Main.cpp 
#Directory to include
INCLUDE = $(shell sdl2-config --cflags)
#Linking Directories
LDFLAGS = $(shell sdl2-config --libs)

OBJECTS = $(BUILD_DIR)Main.o $(BUILD_DIR)Bitmap.o $(BUILD_DIR)Vector3.o $(BUILD_DIR)Window.o $(BUILD_DIR)Vector4f.o

all:$(OUT)
#Linking all the files.
$(OUT):$(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CFLAGS)

#Creating all object files below.
$(BUILD_DIR)Main.o:$(SRC)Main.cpp
	$(CXX) -c $(SRC)Main.cpp $(INCLUDE) -o $(BUILD_DIR)Main.o 

$(BUILD_DIR)Vector3.o:$(SRC)Vector3.cpp $(SRC)Vector3.h
	$(CXX) -c $(SRC)Vector3.cpp $(INCLUDE) -o $(BUILD_DIR)Vector3.o 

$(BUILD_DIR)Bitmap.o:$(SRC)Bitmap.cpp $(SRC)Bitmap.h
	$(CXX) -c $(SRC)Bitmap.cpp $(INCLUDE) -o $(BUILD_DIR)Bitmap.o 

$(BUILD_DIR)Window.o:$(SRC)Window.cpp $(SRC)Window.h
	$(CXX) -c $(SRC)Window.cpp $(INCLUDE) -o $(BUILD_DIR)Window.o 

$(BUILD_DIR)Vector4f.o:$(SRC)Vector4f.cpp $(SRC)Vector4f.h
	$(CXX) -c $(SRC)Vector4f.cpp $(INCLUDE) -o $(BUILD_DIR)Vector4f.o 



#All of the clean up stuff below
clean:
	rm -f $(OUT) $(OBJECTS)
clean_obj:
	rm -f $(OBJECTS)
