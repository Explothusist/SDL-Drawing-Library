
#ifndef Window_Handler_
#define Window_Handler_

#include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h> // DO NOT INCLUDE THIS IN A LIBRARY EVER!
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include <windows.h>
#include <commdlg.h>
#include <iostream>

constexpr int kScreenWidth{ 1000U };
constexpr int kScreenHeight{ 1000U };

/*
Handles interactions with SDL, mimics JS canvas a bit.
*/
class WindowHandler {
    public:
        WindowHandler(std::string window_name);
        virtual ~WindowHandler();

        virtual int init();
        virtual void destroy();
        void renderFrame();

        void clearLayers();

        SDL_Renderer* getRenderer();

        int getScreenWidth();
        int getScreenHeight();

        HWND getWindowHandle();

        WindowHandler(const WindowHandler&) = delete; // Copy constructor
        WindowHandler& operator=(const WindowHandler&) = delete; // Copy assignment operator
        WindowHandler(WindowHandler&&) = delete; // Move constructor
        WindowHandler& operator=(WindowHandler&&) = delete; // Move assignment operator
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        int screenWidth;
        int screenHeight;

        std::string m_window_name;

        // std::vector<SDL_Texture*> m_images;
};

#endif