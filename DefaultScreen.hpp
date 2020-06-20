#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "common.hpp"
class DefaultScreen{
private:
    std::string windowName;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    DefaultScreen(const char* name);
    SDL_Window *getWindow() const;
    SDL_Renderer *getRenderer() const;
    int getResolutionH() const;
    int getResolutionW() const;
    void fillAndColorDefaultScreen();
    void destroy();
};

#endif // WINDOW_HPP_INCLUDED
