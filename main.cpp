#include <iostream>
#include "DefaultScreen.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include "Ball.hpp"

int main(){

    if(SDL_Init(SDL_INIT_VIDEO)==0){
        TTF_Init();
        DefaultScreen screen("Pong");
        if(screen.getWindow()==NULL){
            std::cout << "Could not open window" << std::endl;
            return 1;
        }
        SDL_Renderer* renderer = screen.getRenderer();
        Score scorePlayerLeft{(int)(0.2*RESOLUTION_W)};
        Score scorePlayerRight{(int)(0.8*RESOLUTION_W)};
        bool windowQuit = false;
        while(scorePlayerLeft.getScore()<10 && scorePlayerRight.getScore()<10 && !windowQuit){
            std::cout << "Entered do" << std::endl;
            Player playerLeft{0, RESOLUTION_H/2-PLAYER_HEIGHT/2};
            Player playerRight{RESOLUTION_W-PLAYER_WIDTH, RESOLUTION_H/2-PLAYER_HEIGHT/2};
            Ball ball{renderer};
            ball.createBallBoundary();
            SDL_Event e;
            while(!windowQuit && !ball.atScreenEnd()){
                while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        windowQuit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                                playerRight.moveUp();
                                break;
                            case SDLK_w:
                                playerLeft.moveUp();
                                break;
                            case SDLK_DOWN:
                                playerRight.moveDown();
                                break;
                            case SDLK_s:
                                playerLeft.moveDown();
                                break;
                        }
                    }
                }
                SDL_Delay(GAME_DELAY);
                screen.fillAndColorDefaultScreen();
                playerLeft.fillAndColorPlayer(renderer);
                playerRight.fillAndColorPlayer(renderer);
                scorePlayerLeft.fillAndDisplayScore(renderer);
                scorePlayerRight.fillAndDisplayScore(renderer);
                ball.moveBall(playerLeft, playerRight, scorePlayerLeft, scorePlayerRight);
                ball.renderBall();
                SDL_RenderPresent(renderer);
            }
        }
        screen.destroy();
        SDL_Quit();
    }
    return 0;
}
