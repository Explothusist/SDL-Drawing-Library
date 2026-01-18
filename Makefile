SDL_INCLUDE = -ISDL3\include -ISDL3_image\include -ISDL3_ttf\include -LSDL3\lib -LSDL3_image\lib -LSDL3_ttf\lib -lSDL3 -lSDL3_image -lSDL3_ttf
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