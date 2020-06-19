#ifndef SCORE_HPP_INCLUDED
#define SCORE_HPP_INCLUDED

#include "common.hpp"
#include <sstream>

class Score{
private:
    std::stringstream ss;
    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *surface;
    int locW;
public:
    Score(int locationW);
    ~Score();
    void fillAndDisplayScore(SDL_Renderer *renderer);
    void incrementScore();
};

Score::Score(int locationW){
    font =  TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 25);
    color = {255, 255, 255};
    locW = locationW;
    ss << "0";
}

void Score::fillAndDisplayScore(SDL_Renderer *renderer){
    std::string temp = ss.str();
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
    int score;
    ss >> score;
    ss.str(std::string());
    ss.clear();
    score += 1;
    ss << score;
    //std::cout << ss.str() << std::endl;
}

Score::~Score(){
    TTF_CloseFont(font);
}

#endif // SCORE_HPP_INCLUDED
