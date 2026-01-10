
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

typedef enum {
    Eight_Bit_Plus,
    Olde_English_Regular,
    Playfair_Display,
    Weiss_Run_D
} BuiltinFont;

/*
Handles interactions with SDL, mimics JS canvas a bit.
*/
class DrawingContext : public WindowHandler {
    public:
        DrawingContext(std::string window_name);
        virtual ~DrawingContext();

        int init() override;
        // void destroy() override;

        void fill(int r, int g, int b);
        void fill(int r, int g, int b, int a);
        void fill(SDL_Color color);
        void background(int r, int g, int b);
        void rect(float x, float y, float width, float height);
        void rectOutline(float x, float y, float width, float height);
        void text(std::string txt, float x, float y);
        void text(std::string txt, float x, float y, float width, float vert_spacing);
        // void textCentered(std::string text, float x, float y); // Use textAlign, shapeAlign instead
        void textSize(int size);
        void loadFont(BuiltinFont font);
        void loadFont(std::string font_path);

        void textAlign(Baseline base, Alignment align);
        void shapeAlign(Baseline base, Alignment align);

        int measureTextWidth(std::string text);

        void setTextResizePixelated(bool value); // Use with caution, may not look good

        void presentRenderer();

        DrawingContext(const DrawingContext&) = delete; // Copy constructor
        DrawingContext& operator=(const DrawingContext&) = delete; // Copy assignment operator
        DrawingContext(DrawingContext&&) = delete; // Move constructor
        DrawingContext& operator=(DrawingContext&&) = delete; // Move assignment operator
    private:
        TTF_Font* m_Font;
        SDL_Color m_Color;
        int m_FontSize;
        bool m_ResizeTextPixelated;

        Baseline m_TextBaseline;
        Alignment m_TextAlign;
        Baseline m_ShapeBaseline;
        Alignment m_ShapeAlign;
};

#endif