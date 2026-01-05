
#include "DrawingContext.h"

DrawingContext::DrawingContext(std::string window_name):
    WindowHandler(window_name),
    m_Font{ nullptr },
    m_Color{ 255, 0, 0, 255 },
    m_FontSize{ 30 },
    m_TextBaseline{ BASE_TOP },
    m_TextAlign{ ALIGN_LEFT },
    m_ShapeBaseline{ BASE_TOP },
    m_ShapeAlign{ ALIGN_LEFT }
{

};
DrawingContext::~DrawingContext() {
    destroy();
};

int DrawingContext::init() {
    return WindowHandler::init();
};
void DrawingContext::destroy() {
    TTF_CloseFont(m_Font);
    m_Font = nullptr;

    WindowHandler::destroy();
};

void DrawingContext::fill(int r, int g, int b) {
    m_Color = { static_cast<unsigned char>(r), static_cast<unsigned char>(b), static_cast<unsigned char>(b), 255 };
    SDL_SetRenderDrawColor(getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
};
void DrawingContext::fill(int r, int g, int b, int a) {
    m_Color = { static_cast<unsigned char>(r), static_cast<unsigned char>(b), static_cast<unsigned char>(b), static_cast<unsigned char>(a) };
    SDL_SetRenderDrawColor(getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
};
void DrawingContext::fill(SDL_Color color) {
    m_Color = color;
    SDL_SetRenderDrawColor(getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
};
void DrawingContext::background(int r, int g, int b) {
    SDL_SetRenderDrawColor(getRenderer(), r, g, b, 255);
    SDL_RenderClear(getRenderer());
};
void DrawingContext::rect(float x, float y, float width, float height) {
    SDL_FRect rect = { x, y, width, height };
    if (m_ShapeAlign == ALIGN_CENTER) {
        rect.x -= width / 2;
    }else if (m_ShapeAlign == ALIGN_RIGHT) {
        rect.x -= width;
    }
    if (m_ShapeBaseline == BASE_CENTER) {
        rect.y -= height / 2;
    }else if (m_ShapeBaseline == BASE_BOTTOM) {
        rect.y -= height;
    }
    SDL_RenderFillRect(getRenderer(), &rect);
};
void DrawingContext::text(std::string text, float x, float y) {
    if (m_Font == nullptr) {
        SDL_Log("ERROR: Main: text(): Load Font First");
    }
    SDL_Surface* text_surface = TTF_RenderText_Blended(m_Font, text.c_str(), text.size(), m_Color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), text_surface);

    float size_ratio = m_FontSize/static_cast<float>(texture->h);
    float width = static_cast<float>(texture->w) * size_ratio;
    float height = static_cast<float>(texture->h) * size_ratio;
    SDL_FRect dstRect{ x, y, width, height };
    if (m_TextAlign == ALIGN_CENTER) {
        dstRect.x -= width / 2;
    }else if (m_TextAlign == ALIGN_RIGHT) {
        dstRect.x -= width;
    }
    if (m_TextBaseline == BASE_CENTER) {
        dstRect.y -= height / 2;
    }else if (m_TextBaseline == BASE_BOTTOM) {
        dstRect.y -= height;
    }
    SDL_RenderTexture(getRenderer(), texture, nullptr, &dstRect);

    SDL_DestroySurface(text_surface);
    SDL_DestroyTexture(texture);
};
// void DrawingContext::textCentered(std::string text, float x, float y) {
//     if (m_Font == nullptr) {
//         SDL_Log("ERROR: Main: text(): Load Font First");
//     }
//     SDL_Surface* text_surface = TTF_RenderText_Blended(m_Font, text.c_str(), text.size(), m_Color);
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), text_surface);

//     float size_ratio = m_FontSize/static_cast<float>(texture->h);
//     float width = static_cast<float>(texture->w) * size_ratio;
//     float height = static_cast<float>(texture->h) * size_ratio;
//     SDL_FRect dstRect{ x - (width / 2), y - (height / 2), width, height };
//     SDL_RenderTexture(getRenderer(), texture, nullptr, &dstRect);

//     SDL_DestroySurface(text_surface);
//     SDL_DestroyTexture(texture);
// };
void DrawingContext::textSize(int size) {
    m_FontSize = size;
};
void DrawingContext::loadFont(BuiltinFont font) {
    switch (font) {
        case Eight_Bit_Plus:
            loadFont("SDL-Drawing-Library/fonts/8-bit-operator/8bitOperatorPlus-Regular.ttf");
            break;
        case Olde_English_Regular:
            loadFont("SDL-Drawing-Library/fonts/olde-english-regular/Olde English Regular.ttf");
            break;
        case Playfair_Display:
            loadFont("SDL-Drawing-Library/fonts/playfair-display/PlayfairDisplay-Regular.ttf");
            break;
        case Weiss_Run_D:
            loadFont("SDL-Drawing-Library/fonts/41107_WeissRunD.ttf");
            break;
    }
};
void DrawingContext::loadFont(std::string font_path) {
    TTF_CloseFont(m_Font); // In case there was already a font open

    m_Font = TTF_OpenFont(font_path.c_str(), font_path.size());
    if (m_Font == nullptr) {
        SDL_Log("ERROR: Main: loadFont(): Could not load font %s", font_path.c_str());
    }
};

void DrawingContext::textAlign(Baseline base, Alignment align) {
    m_TextBaseline = base;
    m_TextAlign = align;
};
void DrawingContext::shapeAlign(Baseline base, Alignment align) {
    m_ShapeBaseline = base;
    m_ShapeAlign = align;
};

void DrawingContext::presentRenderer() {
    SDL_RenderPresent(getRenderer());
};