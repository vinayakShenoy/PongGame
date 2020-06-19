#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "common.hpp"

class Player{
private:
    SDL_Rect rect;
public:
    Player(int x, int y);
    void fillAndColorPlayer(SDL_Renderer *renderer);
    void moveUp();
    void moveDown();
    int getPositionY() const;
    bool hasScored() const;
};

#endif // PLAYER_HPP_INCLUDED
