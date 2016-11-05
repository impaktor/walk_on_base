# read about 10.5.3 Automatic variables for Makefiles
# https://www.gnu.org/software/make/manual/make.html

all: walk.cpp jsoncpp.o texture.o
	g++ $^ -o walk -Ljson/ `pkg-config --cflags --libs sdl2` -lSDL2_image

jsoncpp.o: jsoncpp.cpp
	g++ -c jsoncpp.cpp

texture.o: texture.h texture.cpp
	g++ -c texture.cpp
