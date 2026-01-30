
#include "WindowHandler.h"

#include "sdl_drawing_enable_logging.h"

WindowHandler::WindowHandler(std::string window_name):
    m_window{ nullptr },
    m_renderer{ nullptr },
    m_window_name{ window_name }
{

};
WindowHandler::~WindowHandler() {
    clearLayers();

    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();

#ifdef SDL_DRAWING_LOGGING_ENABLED
    SDL_Log("COMPLETE: WindowHandler: destroy()");
#endif
};
int WindowHandler::init() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: init(): SDL Initialization Failed");
#endif
        return 1;
    }

    SDL_CreateWindowAndRenderer(
        m_window_name.c_str(),
        kScreenWidth,
        kScreenHeight,
        SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE,
        &m_window,
        &m_renderer
    );
    if ((m_window == nullptr) || (m_renderer == nullptr)) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: init(): SDL Window and Renderer Creation Failed");
#endif
        return 2;
    }

    if (!SDL_SetRenderVSync(m_renderer, 1)) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: init(): SDL VSync Enabling Failed");
#endif
        return 3;
    }

    if (!TTF_Init()) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: init(): SDL TTF Initialization Failed");
#endif
        return 4;
    }

#ifdef SDL_DRAWING_LOGGING_ENABLED
    SDL_Log("COMPLETE: WindowHandler: init()");
#endif
    return 0;
};
// void WindowHandler::destroy() {
// };
void WindowHandler::renderFrame() {
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
};
void WindowHandler::clearLayers() {

};
SDL_Renderer* WindowHandler::getRenderer() {
    return m_renderer;
};

int WindowHandler::getScreenWidth() {
    bool success = SDL_GetWindowSizeInPixels(m_window, &screenWidth, &screenHeight);
    if (!success) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: getScreenWidth(): Get Window Size Failed");
#endif
    }
    return screenWidth;
};
int WindowHandler::getScreenHeight() {
    bool success = SDL_GetWindowSizeInPixels(m_window, &screenWidth, &screenHeight);
    if (!success) {
#ifdef SDL_DRAWING_LOGGING_ENABLED
        SDL_Log("ERROR: WindowHandler: getScreenHeight(): Get Window Size Failed");
#endif
    }
    return screenHeight;
};

HWND WindowHandler::getWindowHandle() {
    // return (HWND)SDL_GetWindowData(sdlWindow, "HWND");
    return FindWindowA(NULL, m_window_name.c_str());
}