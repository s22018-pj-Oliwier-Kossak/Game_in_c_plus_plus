
#include <SDL2/SDL.h>
const int WIDTH = 800, HEIGHT = 600;
int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Canon Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                   SDL_WINDOW_SHOWN);
    int gaming = true;

    while (gaming){
        SDL_Event event;
        while(SDL_PollEvent(&event) !=0){
            switch(event.type){
            case SDL_QUIT:
                gaming = false;
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
