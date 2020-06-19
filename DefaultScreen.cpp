#include "DefaultScreen.hpp"

DefaultScreen::DefaultScreen(const char *name){
    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              RESOLUTION_W,
                              RESOLUTION_H,
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

void DefaultScreen::fillAndColorDefaultScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, RESOLUTION_W/2, 0, RESOLUTION_W/2, RESOLUTION_H);
}

void DefaultScreen::destroy(){
    SDL_DestroyWindow(window);
}
