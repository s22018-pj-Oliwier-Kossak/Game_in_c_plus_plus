
#include <SDL2/SDL.h>


bool handle_events(SDL_Rect &rect);

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("cannon game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1000,800,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);



    SDL_Rect rect;
    rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;

    auto prev_ticks = SDL_GetTicks64();
    int frame_dropped = 0;

    while (handle_events(rect)){
        if (!frame_dropped){

            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);

        }

        auto ticks = SDL_GetTicks64();
        if ((ticks - prev_ticks) < 33){
            SDL_Delay(33 - (ticks - prev_ticks));
            frame_dropped = 0;
        }
        else{frame_dropped = 1;}
        prev_ticks += 33;

    }

    SDL_DestroyWindow(window);



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




