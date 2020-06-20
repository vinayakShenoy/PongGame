#include "Ball.hpp"

Ball::Ball(SDL_Renderer *renderer){
    this->renderer = renderer;
    ballRadius = 8;
    centerX = RESOLUTION_W/2;
    centerY = RESOLUTION_H/2;
    lineInclination = 0;
    slope = 0;
    yIntercept = RESOLUTION_H/2;
    positiveDirection = false;
    ballReachedScreenEnd = false;
    isReflecting = false;
}

bool Ball::atScreenEnd() const{
    return ballReachedScreenEnd;
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
    std::cout << "1. Before reflection details: " <<  y1 << " " << lineInclination << " " << yIntercept << std::endl;
    lineInclination = 180 - lineInclination;
    yIntercept = y1 - std::tan((PI/180)*lineInclination)*centerX;
    std::cout << "2. After reflection details: " <<  y1 << " " << lineInclination << " " << yIntercept << std::endl;
}

//Deflection when ball touches player
//Find the distance of ball from mid of player and apply new deflection angle.
void Ball::deflectionLine(const Player &pl){
    int playerMidY = pl.getPositionY() + PLAYER_HEIGHT/2;
    int newAngle = BALL_ON_PLAYER_DEFLECTION_UNIT*(centerY - playerMidY);
    if(positiveDirection)
        newAngle = -1*newAngle;
    lineInclination = (180 - newAngle)%180;
    yIntercept = centerY - std::tan((PI/180)*lineInclination)*centerX;
}

//
void Ball::moveBall(const Player &playerLeft, const Player &playerRight, Score &left, Score &right){
    if(((centerY - ballRadius) < 0) && !isReflecting){
        reflectLine(0);
        isReflecting = true;
    }
    else if(((centerY + ballRadius) > RESOLUTION_H) && !isReflecting){
        reflectLine(centerY);
        isReflecting = true;
    }
    else if(isReflecting && ((centerY - ballRadius) >= 0) && ((centerY + ballRadius) <= RESOLUTION_H)){
        isReflecting = false;
    }
    //Ball touches left end of screen. Player Right wins
    if((centerX - ballRadius) < 0){
        right.incrementScore();
        ballReachedScreenEnd = true;
        positiveDirection = false;
    }
    //Ball touches right end of screen. Player left wins
    else if((centerX + ballRadius) > RESOLUTION_W){
        left.incrementScore();
        ballReachedScreenEnd = true;
        positiveDirection = true;
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
    centerY = std::tan((PI/180)*lineInclination)*centerX + yIntercept;
}
