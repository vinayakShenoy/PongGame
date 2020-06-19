#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED
#include "common.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include <math.h>

class Ball{
private:
    SDL_Renderer *renderer;
    int ballRadius;
    int centerX;
    int centerY;
    int lineInclination;
    double slope;
    double yIntercept;
    bool positiveDirection;
    bool screenEndReached;
    std::vector<SDL_Point> points;
    std::vector<SDL_Point> outerLayer;
    void addToPointArray(int x, int y);
    void midPointAlgo(int p0, int x, int y);
    void deflectionLine(const Player &pl);
    void reflectLine(int y1);
public:
    Ball(SDL_Renderer *renderer);
    void createBallBoundary();
    void renderBall();
    void moveBall(const Player &playerLeft, const Player &playerRight, Score &left, Score &right);
};

Ball::Ball(SDL_Renderer *renderer){
    this->renderer = renderer;
    ballRadius = 8;
    centerX = RESOLUTION_W/2;
    centerY = RESOLUTION_H/2;
    lineInclination = 0;
    slope = 0;
    yIntercept = RESOLUTION_H/2;
    positiveDirection = true;
}

void Ball::addToPointArray(int x, int y){
    points.push_back({x,y});
    points.push_back({x,-y});
    points.push_back({-x,-y});
    points.push_back({-x,y});
    points.push_back({y,x});
    points.push_back({y,-x});
    points.push_back({-y,-x});
    points.push_back({-y,x});
}

void Ball::midPointAlgo(int p0, int x, int y){
    addToPointArray(x, y);
    int x1 = x+1;
    int y1;
    if(p0<0)
        y1 = y;
    else
        y1 = y-1;
    if(x1>y1)
        return;
    int p1 = p0 + 2*(x1+1) + (y1*y1-y*y) - (y1-y) + 1;
    midPointAlgo(p1, x1, y1);
}

void Ball::createBallBoundary(){
    int p0 = 1 - ballRadius;
    for(int i = ballRadius;i>1;i--){
        midPointAlgo(p0, 0, i);
        if(i==ballRadius){
            outerLayer = points;
        }
    }
}

void Ball::renderBall(){
    std::vector<SDL_Point> vt = points;
    for(SDL_Point &point: vt){
        point.x += centerX;
        point.y += centerY;
    }
    vt.push_back({centerX,centerY});
    const SDL_Point *pts = &vt[0];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoints(renderer, pts, points.size());
}

//(x1,y1): center of ball when ball touches upper/lower Y boundaries
//slope of reflected line(slope theta) is 180-theta
void Ball::reflectLine(int y1){
    lineInclination = 180 - lineInclination;
    yIntercept = y1 - std::tan(lineInclination)*centerX;
    //std::cout << lineInclination << std::endl;
}

//Deflection when ball touches player
//Find the distance of ball from mid of player and apply new deflection angle.
void Ball::deflectionLine(const Player &pl){
    int playerMidY = pl.getPositionY() + PLAYER_HEIGHT/2;
    int newAngle = BALL_ON_PLAYER_DEFLECTION_UNIT*(centerY - playerMidY);
    lineInclination = (180 - newAngle)%180;
    yIntercept = centerY - std::tan(lineInclination)*centerX;
    std::cout <<  playerMidY << " " << BALL_ON_PLAYER_DEFLECTION_UNIT << " " << centerY << " " << lineInclination << std::endl;
}

//
void Ball::moveBall(const Player &playerLeft, const Player &playerRight, Score &left, Score &right){
    if((centerY - ballRadius) < 0){
        reflectLine(0);
    }
    else if((centerY + ballRadius) > RESOLUTION_H){
        reflectLine(centerY);
    }
    //Ball touches left end of screen. Player Right wins
    if((centerX - ballRadius) < 0){
        right.incrementScore();
        screenEndReached = true;
    }
    //Ball touches right end of screen. Player left wins
    else if((centerX + ballRadius) > RESOLUTION_W){
        left.incrementScore();
        screenEndReached = true;
    }
    //Ball touches surface of player left
    else if((centerX - ballRadius) < PLAYER_WIDTH){
        if(centerY > playerLeft.getPositionY() && centerY < (playerLeft.getPositionY() + PLAYER_HEIGHT)){
            positiveDirection = true;
            deflectionLine(playerLeft);
        }
    }
    //ball touches surface of player right
    else if((centerX + ballRadius) > (RESOLUTION_W - PLAYER_WIDTH)){
        if(centerY > playerRight.getPositionY() && centerY < (playerRight.getPositionY() + PLAYER_HEIGHT)){
            positiveDirection = false;
            deflectionLine(playerRight);
        }
    }
    centerX = positiveDirection?(centerX + BALL_MOVE_DELTA):(centerX - BALL_MOVE_DELTA);
    centerY = std::tan(lineInclination)*centerX + yIntercept;
}





#endif // BALL_HPP_INCLUDED
