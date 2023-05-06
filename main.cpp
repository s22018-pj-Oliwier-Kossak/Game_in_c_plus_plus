
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;

SDL_Window *window;
SDL_Surface *background ;
SDL_Surface *screen_surface;

bool handle_events();
bool load_background();

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("cannon game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1100,800,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    background = SDL_LoadBMP("background.bmp");
    screen_surface = SDL_GetWindowSurface( window );


    auto prev_ticks = SDL_GetTicks64();
    int frame_dropped = 0;

    while (true){

        if (!frame_dropped){

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            SDL_BlitSurface( background, NULL, screen_surface, NULL );
            SDL_UpdateWindowSurface( window );

        }

        auto ticks = SDL_GetTicks64();
        if ((ticks - prev_ticks) < 2){
            SDL_Delay(70 - (ticks - prev_ticks));
            frame_dropped = 0;
            SDL_UpdateWindowSurface( window );
        }
        else{frame_dropped = 1;}
        prev_ticks += 33;

    }

    SDL_DestroyWindow(window);



    return 0;
}

/*bool load_background(){

    bool success = true;

	background = SDL_LoadBMP("background.bmp");
	return success;
} */

bool handle_events(){
    /*function to catch events*/
  auto *key_state = SDL_GetKeyboardState(nullptr);
  SDL_Event event;
        while(SDL_PollEvent(&event) !=0){
            switch(event.type){
            case SDL_QUIT:
                return false;

            }
        }
   /* if (key_state[SDL_SCANCODE_UP]){
        rect.y -=5;
    }
    if (key_state[SDL_SCANCODE_DOWN]){
        rect.y +=5;
    }
*/
    return true;
}




