#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "common.hpp"

class Player{
private:
    SDL_Rect rect;
    int rect_h;
    int rect_w;
public:
    Player(int x, int y);
    void fillAndColorPlayer(SDL_Renderer *renderer);
    void moveUp();
    void moveDown();
};

Player::Player(int x, int y){
    rect.h = 50;
    rect.w = 15;
    rect.x = x;
    rect.y = y;
}

void Player::fillAndColorPlayer(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect(renderer, &rect);
}

void Player::moveUp(){
    if((rect.y-10)<=0){
        rect.y = 0;
    }
    else{
        rect.y -= 10;
    }
}

void Player::moveDown(){
    if((rect.y+rect.h+10)>=480){
        rect.y = 480-rect.h;
    }
    else{
        rect.y += 10;
    }
}
#endif // PLAYER_HPP_INCLUDED
