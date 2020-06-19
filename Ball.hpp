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
    bool ballReachedScreenEnd;
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
    bool atScreenEnd() const;
};





#endif // BALL_HPP_INCLUDED
