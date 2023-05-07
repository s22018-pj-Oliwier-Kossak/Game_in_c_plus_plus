
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>

SDL_Window *window;
SDL_Surface *background ;
SDL_Surface *cannon ;
SDL_Surface *screen_surface;
SDL_Surface* bullet ;
SDL_Surface* block ;
float canon_speed_x = 0;
float canon_speed_y = 0;
float canon_power_shoot_x=0;
float canon_power_shoot_y=0;

bool handle_events(SDL_Rect &rect,SDL_Rect &rect2);
void shoot_bullet(SDL_Rect &rect2,SDL_Rect &rect);
void collison_bullet(SDL_Rect &rect,SDL_Rect &rect2);


int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("cannon game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1100,800,SDL_WINDOW_SHOWN);
    //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    background = SDL_LoadBMP("assets/background.bmp");
    screen_surface = SDL_GetWindowSurface( window );
    cannon = SDL_LoadBMP("assets/cannon.bmp");
    bullet = SDL_LoadBMP("assets/bullet.bmp");
    block = SDL_LoadBMP("assets/block.bmp");


    SDL_Rect rect_cannon;
    rect_cannon.x = 44;
    rect_cannon.y = 590;
    rect_cannon.w = 0;
    rect_cannon.h = 0;

    SDL_Rect rect_bullet;
    rect_bullet.x = 25;
    rect_bullet.y = rect_cannon.y  + 30;
    rect_bullet.w = 10;
    rect_bullet.h = 10;

    SDL_Rect rect_block;
    rect_block.x = 560;
    rect_block.y = 100;
    rect_block.w = 40;
    rect_block.h = 40;



    auto prev_ticks = SDL_GetTicks64();
    int frame_dropped = 0;
    SDL_UpdateWindowSurface( window );

    while (handle_events(rect_cannon, rect_bullet)){
        SDL_UpdateWindowSurface( window );

        if (!frame_dropped){

            //SDL_RenderClear(renderer);
            //SDL_RenderPresent(renderer);
            SDL_BlitSurface( background, NULL, screen_surface, NULL );
            SDL_BlitSurface( cannon, NULL, screen_surface,  &rect_cannon );
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block);
            collison_bullet(rect_bullet,rect_block);
            shoot_bullet(rect_bullet,rect_cannon);
            rect_bullet.y -=canon_speed_y;
            rect_bullet.x +=canon_speed_x ;

            //std::cout<<rect_bullet.y<<std::endl;
            SDL_BlitSurface( bullet, NULL, screen_surface, &rect_bullet );
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
void collison_bullet(SDL_Rect &rect,SDL_Rect &rect2){
    if(rect.x>1110 || rect.y > 810){
            rect.y = rect.y  + 30;
            rect.x = 25;
            canon_speed_y = 0;
            canon_speed_x = 0;
    }
    if(((rect.x+rect.w >=rect2.x) &&(rect.x+rect.w<=rect2.x+rect2.w))&&((rect.y+rect.w>=rect2.y) &&(rect.y+rect.w<=rect2.y+rect2.h))){
         std::cout<<"col"<<std::endl;
         canon_speed_y = -25;
         canon_speed_x = -10;

    }



}

void shoot_bullet(SDL_Rect &rect2,SDL_Rect &rect){

        if(rect2.x <150 ){

        auto *key_state = SDL_GetKeyboardState(nullptr);
            if (key_state[SDL_SCANCODE_P]){


                     canon_power_shoot_x += 2.5;
                     canon_power_shoot_y += 1;

                }
            if (key_state[SDL_SCANCODE_O]){

                    if((canon_power_shoot_x<0)||(canon_power_shoot_y<0))
                       {
                           canon_power_shoot_x = 0;
                           canon_power_shoot_y = 0;
                       }
                    else
                        {
                            canon_power_shoot_x += -2.5;
                            canon_power_shoot_y += -1;
                        }

                }


            if (key_state[SDL_SCANCODE_SPACE]){

                     rect2.y = rect.y  + 30;
                     rect2.x = 115;
                     canon_speed_x = canon_power_shoot_x+25;
                     canon_speed_y = canon_power_shoot_y +10;
                     std::cout<<canon_speed_x<<std::endl;

                }
            }

        else if((rect2.x >=150) && (rect2.x <400)){

            canon_speed_x += -0.5;
            canon_speed_y += 0.5;
        }

        else if((rect2.x>=400) && (rect2.x<1110)){
            canon_speed_x += 0.5;
            canon_speed_y +=-1.75;
        }
        else if(rect2.x>1110 || rect2.y > 810){
            rect2.y = rect.y  + 30;
            rect2.x = 25;
            canon_speed_y = 0;
            canon_speed_x = 0;
        }

}

bool handle_events(SDL_Rect &rect,SDL_Rect &rect2){
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

        if(rect.y < 250)
            {
                rect.y +=0;
            }

        else
            {
                rect.y -=5;
            }
    }

    if (key_state[SDL_SCANCODE_DOWN]){

         if(rect.y < 615)
            {
                rect.y +=5;
            }
        else
            {

                rect.y -=0;
            }

    }

    return true;
}


