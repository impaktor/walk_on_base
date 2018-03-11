# read about 10.5.3 Automatic variables for Makefiles
# https://www.gnu.org/software/make/manual/make.html

CXX = g++
SDL_LIB = `pkg-config --cflags --libs sdl2` -lSDL2_image
SDL_INCLUDE = -I/usr/local/include
FLAGS = -Wall -Wextra -pedantic -Wno-switch -c -std=c++11 $(SDL_INCLUDE) -O0 -g3
LDFLAGS = $(SDL_LIB) -Ljson/
EXECUTABLE = walk

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(EXECUTABLE)

.cpp.o: Makedep.rule
	$(CXX) $(FLAGS) -o $@ $<

depend:
	$(CXX) $(FLAGS) -MM $(SRC) >Makedep.rule

Makedep.rule: Makefile
	@echo "The makefile has changed since the last 'make depend'."

$(EXECUTABLE): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^
#	$(CXX) $(LDFLAGS) -o $@ $+
#	$(CXX) $< $(LDFLAGS) -o $@ $+

clean:
	rm *.o && rm $(EXECUTABLE)
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
