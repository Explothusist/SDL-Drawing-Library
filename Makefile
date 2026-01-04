SDL_INCLUDE = -Ix86_64-w64-mingw32\include -Lx86_64-w64-mingw32\lib -lSDL3 -lSDL3_image -lSDL3_ttf
WINDOW_INCLUDE = DrawingContext.o WindowHandler.o
HELPER_INCLUDE = $(WINDOW_INCLUDE)

all: $(HELPER_INCLUDE)
	
DrawingContext.o: WindowHandler.o DrawingContext.cpp
	g++ -Wall -c DrawingContext.cpp $(SDL_INCLUDE) -o DrawingContext.o

WindowHandler.o: WindowHandler.cpp
	g++ -Wall -c WindowHandler.cpp $(SDL_INCLUDE) -o WindowHandler.o

clean:
	del main.exe

cleanAll:
	del main.exe $(HELPER_INCLUDE)