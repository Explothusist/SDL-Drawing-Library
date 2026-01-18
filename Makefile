SDL_BASE = SDL3-3.4.0
SDL_IMAGE = SDL3_image-3.2.6
SDL_TTF = SDL3_ttf-3.2.2

SDL_CFLAGS = -I$(SDL_BASE)/include -I$(SDL_IMAGE)/include -I$(SDL_TTF)/include
SDL_LDFLAGS = -L$(SDL_BASE)/lib -L$(SDL_IMAGE)/lib -L$(SDL_TTF)/lib -lSDL3 -lSDL3_image -lSDL3_ttf
WINDOW_OBJS = DrawingContext.o WindowHandler.o
OBJS = $(WINDOW_OBJS)

all: $(OBJS)
	
DrawingContext.o: DrawingContext.cpp DrawingContext.h
	g++ -Wall -c DrawingContext.cpp $(SDL_CFLAGS) -o DrawingContext.o

WindowHandler.o: WindowHandler.cpp WindowHandler.h
	g++ -Wall -c WindowHandler.cpp $(SDL_CFLAGS) -o WindowHandler.o

clean:
	del $(OBJS)

cleanAll:
	del $(OBJS)

.PHONY: all clean cleanAll