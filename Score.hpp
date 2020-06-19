#ifndef SCORE_HPP_INCLUDED
#define SCORE_HPP_INCLUDED

#include "common.hpp"
#include <sstream>

class Score{
private:
    std::stringstream score;
    TTF_Font *font;
    SDL_Color color;
    SDL_Surface *surface;
    int locW;
public:
    Score(int locationW);
    ~Score();
    void fillAndDisplayScore(SDL_Renderer *renderer);
    void incrementScore();
    int getScore();
};



#endif // SCORE_HPP_INCLUDED
