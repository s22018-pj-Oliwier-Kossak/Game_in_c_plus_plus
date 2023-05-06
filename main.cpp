
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

SDL_Window *window;
SDL_Surface *background ;
SDL_Surface *cannon ;
SDL_Surface *screen_surface;


bool handle_events(SDL_Rect &rect);

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("cannon game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1100,800,SDL_WINDOW_SHOWN);
    //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    background = SDL_LoadBMP("assets/background.bmp");
    screen_surface = SDL_GetWindowSurface( window );
    cannon = SDL_LoadBMP("assets/cannon.bmp");




    SDL_Rect rect;
    rect.x = 44;
    rect.y = 590;
    rect.w = 35;
    rect.h = 590;

    auto prev_ticks = SDL_GetTicks64();
    int frame_dropped = 0;
    SDL_UpdateWindowSurface( window );
    while (handle_events(rect)){
        SDL_UpdateWindowSurface( window );

        if (!frame_dropped){

            //SDL_RenderClear(renderer);
            //SDL_RenderPresent(renderer);
            SDL_BlitSurface( background, NULL, screen_surface, NULL );
            SDL_BlitSurface( cannon, NULL, screen_surface,  &rect );
            SDL_UpdateWindowSurface( window );

        }

        auto ticks = SDL_GetTicks64();

        if ((ticks - prev_ticks) < 33){
            SDL_Delay(33 - (ticks - prev_ticks));
            frame_dropped = 0;


        }

        else{frame_dropped = 1;}

        prev_ticks += 33;

    }



    //SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool handle_events(SDL_Rect &rect){
    /*function to catch events*/
  auto *key_state = SDL_GetKeyboardState(nullptr);
  SDL_Event event;
        while(SDL_PollEvent(&event) !=0){
            switch(event.type){
            case SDL_QUIT:
                return false;

            }
        }
    if (key_state[SDL_SCANCODE_UP]){
        rect.y -=5;
    }
    if (key_state[SDL_SCANCODE_DOWN]){
        rect.y +=5;
    }

    return true;
}


