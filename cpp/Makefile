# read about 10.5.3 Automatic variables for Makefiles
# https://www.gnu.org/software/make/manual/make.html

CXX = g++
#CXX = clang++
EXECUTABLE = walk
SDL_INCLUDE = -I/usr/local/include
IMGUI_DIR = imgui

SRC = $(wildcard *.cpp)
SRC += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SRC += $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_sdlrenderer.cpp

OBJ = $(SRC:.cpp=.o)

LIBS = -lGL -ldl `sdl2-config --libs` -lSDL2_image -Ljson/

CXXFLAGS = -Wall -Wformat -Wextra -pedantic -Wno-switch $(SDL_INCLUDE) -O0 -g3
CXXFLAGS += -std=c++11 -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += `sdl2-config --cflags`
CFLAGS = $(CXXFLAGS)

all: $(EXECUTABLE)
	@echo Build complete

.cpp.o: Makedep.rule
	$(CXX) $(CXXFLAGS) -c -o $@ $<

depend:
	$(CXX) $(CXXFLAGS) -c -MM $(SRC) >Makedep.rule

Makedep.rule: Makefile
	@echo "The makefile has changed since the last 'make depend'."

$(EXECUTABLE): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm $(OBJ) && rm $(EXECUTABLE)
	make depend

lines:
	wc -l $(SRC) *.h

.PHONY: all clean depend lines

# Dependencies for makefile
include Makedep.rule


# all: walk.cpp jsoncpp.o texture.o
#	g++ $^ -o walk -Ljson/ `pkg-config --cflags --libs sdl2` -lSDL2_image

# jsoncpp.o: jsoncpp.cpp
#	g++ -c jsoncpp.cpp

# texture.o: texture.h texture.cpp
#	g++ -c texture.cpp
