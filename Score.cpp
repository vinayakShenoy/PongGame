#include "Score.hpp"

Score::Score(int locationW){
    font =  TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 25);
    color = {255, 255, 255};
    locW = locationW;
    score << "0";
}

void Score::fillAndDisplayScore(SDL_Renderer *renderer){
    std::string temp = score.str();
    const char* ch = temp.c_str();
    SDL_Surface *surface = TTF_RenderText_Solid(font, ch, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect dstrect = {locW,0,textW,textH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void Score::incrementScore(){
    int sc = 0;
    score >> sc;
    sc += 1;
    score.str(std::string());
    score.clear();
    score << sc;
}

Score::~Score(){
    TTF_CloseFont(font);
}

int Score::getScore(){
    int sc = 0;
    score >> sc;
    score.clear();
    score.seekg(0, std::ios::beg);
    return sc;
}
