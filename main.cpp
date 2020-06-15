#include <iostream>
#include "DefaultScreen.hpp"
#include "Player.hpp"

int main(){
    int RESOLUTION_H = 480;
    int RESOLUTION_W = 640;

    if(SDL_Init(SDL_INIT_VIDEO)==0){
        DefaultScreen screen(RESOLUTION_W, RESOLUTION_H, "Pong");
        if(screen.getWindow()==NULL){
            std::cout << "Could not open window" << std::endl;
            return 1;
        }
        screen.fillAndColorDefaultScreen();
        SDL_Renderer* renderer = screen.getRenderer();
        SDL_RenderPresent(renderer);

        Player player1(0, 240);
        Player player2(625, 240);
        player1.fillAndColorPlayer(renderer);
        player2.fillAndColorPlayer(renderer);
        SDL_RenderPresent(renderer);


        bool quit = false;
        SDL_Event e;
        while(!quit){
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    quit = true;
                }
                else if(e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_UP:
                            std::cout << "Moving up" << std::endl;
                            player1.moveUp();
                            player2.moveUp();
                            break;
                        case SDLK_DOWN:
                            std::cout << "Moving down" << std::endl;
                            player1.moveDown();
                            player2.moveDown();
                            break;
                    }
                }
                //reset original screen
                screen.fillAndColorDefaultScreen();
                player1.fillAndColorPlayer(renderer);
                player2.fillAndColorPlayer(renderer);
            }
            SDL_RenderPresent(renderer);
        }
        screen.destroy();
        SDL_Quit();
    }
    return 0;
}
