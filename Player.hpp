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
};
Player::Player(int x, int y){
    rect.h = PLAYER_HEIGHT;
    rect.w = PLAYER_WIDTH;
    rect.x = x;
    rect.y = y;
}

void Player::fillAndColorPlayer(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect(renderer, &rect);
}

void Player::moveUp(){
    if((rect.y - PLAYER_MOVE_DELTA)<=0){
        rect.y = 0;
    }
    else{
        rect.y -= PLAYER_MOVE_DELTA;
    }
}

void Player::moveDown(){
    if((rect.y + rect.h + PLAYER_MOVE_DELTA) >= RESOLUTION_H){
        rect.y = RESOLUTION_H - rect.h;
    }
    else{
        rect.y += PLAYER_MOVE_DELTA;
    }
}

int Player::getPositionY() const{
    return rect.y;
}
#endif // PLAYER_HPP_INCLUDED
