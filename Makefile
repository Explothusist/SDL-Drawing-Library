SDL_INCLUDE = -Ix86_64-w64-mingw32\include -Lx86_64-w64-mingw32\lib -lSDL3 -lSDL3_image -lSDL3_ttf
WINDOW_INCLUDE = window\DrawingContext.o window\WindowHandler.o
HELPER_INCLUDE = $(WINDOW_INCLUDE)

all: $(HELPER_INCLUDE)
	
DrawingContext.o: window\WindowHandler.o window\DrawingContext.cpp
	g++ -Wall -c window\DrawingContext.cpp $(SDL_INCLUDE) -o window\DrawingContext.o

WindowHandler.o: window\WindowHandler.cpp
	g++ -Wall -c window\WindowHandler.cpp $(SDL_INCLUDE) -o window\WindowHandler.o

clean:
	del main.exe

cleanAll:
	del main.exe $(HELPER_INCLUDE)