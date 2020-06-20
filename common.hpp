#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <array>

const short PLAYER_HEIGHT = 50;
const short PLAYER_WIDTH = 15;
const int RESOLUTION_H = 480;
const int RESOLUTION_W = 640;
const int GAME_DELAY = 5;
const int PLAYER_MOVE_DELTA = 3;
const int BALL_MOVE_DELTA = 1;
const int BALL_RADIUS = 8;
const int MAX_DEFLECTION_DEGREES = 75;
const int BALL_ON_PLAYER_DEFLECTION_UNIT = MAX_DEFLECTION_DEGREES/(PLAYER_HEIGHT/2);
const long double PI = 3.141592653589793238;

#endif // COMMON_HPP_INCLUDED
