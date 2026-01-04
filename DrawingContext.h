
#ifndef Drawing_Context_
#define Drawing_Context_

#include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h> // DO NOT INCLUDE THIS IN A LIBRARY EVER!
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

#include "WindowHandler.h"

typedef enum {
    BASE_TOP,
    BASE_CENTER,
    BASE_BOTTOM
} Baseline;
typedef enum {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} Alignment;

/*
Handles interactions with SDL, mimics JS canvas a bit.
*/
class DrawingContext : public WindowHandler {
    public:
        DrawingContext(std::string window_name);
        ~DrawingContext();

        int init() override;
        void destroy() override;

        void fill(int r, int g, int b);
        void fill(int r, int g, int b, int a);
        void fill(SDL_Color color);
        void background(int r, int g, int b);
        void rect(float x, float y, float width, float height);
        void text(std::string text, float x, float y);
        // void textCentered(std::string text, float x, float y); // Use textAlign, shapeAlign instead
        void textSize(int size);
        void loadFont(std::string font_path);

        void textAlign(Baseline base, Alignment align);
        void shapeAlign(Baseline base, Alignment align);

        void presentRenderer();

        DrawingContext(const DrawingContext&) = delete; // Copy constructor
        DrawingContext& operator=(const DrawingContext&) = delete; // Copy assignment operator
        DrawingContext(DrawingContext&&) = delete; // Move constructor
        DrawingContext& operator=(DrawingContext&&) = delete; // Move assignment operator
    private:
        TTF_Font* m_Font;
        SDL_Color m_Color;
        int m_FontSize;

        Baseline m_TextBaseline;
        Alignment m_TextAlign;
        Baseline m_ShapeBaseline;
        Alignment m_ShapeAlign;
};

#endif