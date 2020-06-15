#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "common.hpp"
class DefaultScreen{
private:
    int resolutionH;
    int resolutionW;
    std::string windowName;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    DefaultScreen(int w, int h, const char* name);
    SDL_Window *getWindow() const;
    SDL_Renderer *getRenderer() const;
    int getResolutionH() const;
    int getResolutionW() const;
    void fillAndColorDefaultScreen();
    void destroy();
};

DefaultScreen::DefaultScreen(int w, int h, const char *name){
    resolutionH = h;
    resolutionW = w;
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              resolutionW,
                              resolutionH,
                              SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED);
}

SDL_Window *DefaultScreen::getWindow() const{
    return window;
}
SDL_Renderer *DefaultScreen::getRenderer() const{
    return renderer;
}
int DefaultScreen::getResolutionH() const{
    return resolutionH;
}

int DefaultScreen::getResolutionW() const{
    return resolutionW;
}

void DefaultScreen::fillAndColorDefaultScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
}

void DefaultScreen::destroy(){
    SDL_DestroyWindow(window);
}

#endif // WINDOW_HPP_INCLUDED
