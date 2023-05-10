
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <random>

SDL_Window *window;
SDL_Surface *screen_surface;
SDL_Surface *background ;
SDL_Surface *cannon ;
SDL_Surface *bullet ;
SDL_Surface *block ;
SDL_Surface *block_king;

float canon_speed_x = 0;
float canon_speed_y = 0;
float canon_power_shoot_x = 0;
float canon_power_shoot_y = 0;
int count_shoot = 3;
int points = 0;

bool handle_events(SDL_Rect &rect, SDL_Rect &rect2);
void collison_bullet_block(SDL_Rect &rect,SDL_Rect &rect2, SDL_Rect &rect3);
void collison_bullet_king(SDL_Rect &rect,SDL_Rect &rect2,SDL_Rect &rect3);
void display_shoot_counter();
void display_shoot_and_point_counter();


int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("cannon game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,1100,800,SDL_WINDOW_SHOWN);
    screen_surface = SDL_GetWindowSurface( window );
    background = SDL_LoadBMP("assets/background.bmp");
    cannon = SDL_LoadBMP("assets/cannon.bmp");
    bullet = SDL_LoadBMP("assets/bullet.bmp");
    block = SDL_LoadBMP("assets/block.bmp");
    block_king = SDL_LoadBMP("assets/king.bmp");


    SDL_Rect rect_cannon;
    rect_cannon.x = 44;
    rect_cannon.y = 590;
    rect_cannon.w = 0;
    rect_cannon.h = 0;

    SDL_Rect rect_bullet;
    rect_bullet.x = 25;
    rect_bullet.y = rect_cannon.y  + 30;
    rect_bullet.w = 15;
    rect_bullet.h = 15;

    SDL_Rect rect_block;
    rect_block.x = 560;
    rect_block.y = 100;
    rect_block.w = 40;
    rect_block.h = 40;

    SDL_Rect rect_block2;
    rect_block2.x = 570;
    rect_block2.y = 330;
    rect_block2.w = 40;
    rect_block2.h = 40;

    SDL_Rect rect_block3;
    rect_block3.x = 790;
    rect_block3.y = 150;
    rect_block3.w = 40;
    rect_block3.h = 40;

    SDL_Rect rect_block4;
    rect_block4.x = 730;
    rect_block4.y = 90;
    rect_block4.w = 40;
    rect_block4.h = 40;

    SDL_Rect rect_block5;
    rect_block5.x = 690;
    rect_block5.y = 260;
    rect_block5.w = 40;
    rect_block5.h = 40;

    SDL_Rect rect_block6;
    rect_block6.x = 790;
    rect_block6.y = 325;
    rect_block6.w = 40;
    rect_block6.h = 40;

    SDL_Rect rect_block_king;
    rect_block_king.x = 950;
    rect_block_king.y = 230;
    rect_block_king.w = 40;
    rect_block_king.h = 40;

    auto prev_ticks = SDL_GetTicks64();
    int frame_dropped = 0;

    display_shoot_and_point_counter();

    while (handle_events(rect_cannon, rect_bullet)){
        SDL_UpdateWindowSurface( window );

        if (!frame_dropped){


            SDL_BlitSurface( background, NULL, screen_surface, NULL );
            SDL_BlitSurface( cannon, NULL, screen_surface,  &rect_cannon );
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block);
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block2);
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block3);
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block4);
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block5);
            SDL_BlitSurface( block, NULL, screen_surface,  &rect_block6);
            SDL_BlitSurface( block_king, NULL, screen_surface,  &rect_block_king);
            collison_bullet_block(rect_bullet, rect_block, rect_cannon);
            collison_bullet_block(rect_bullet, rect_block2, rect_cannon);
            collison_bullet_block(rect_bullet,rect_block3, rect_cannon);
            collison_bullet_block(rect_bullet,rect_block4, rect_cannon);
            collison_bullet_block(rect_bullet,rect_block5, rect_cannon);
            collison_bullet_block(rect_bullet,rect_block6, rect_cannon);
            collison_bullet_king(rect_bullet,rect_block_king, rect_cannon);

            SDL_BlitSurface( bullet, NULL, screen_surface, &rect_bullet );
            SDL_UpdateWindowSurface( window );
        }

        int ticks = SDL_GetTicks64();

        if ((ticks - prev_ticks) < 33){
            SDL_Delay(33 - (ticks - prev_ticks));
            frame_dropped = 0;


        }
        else{frame_dropped = 1;}
        prev_ticks += 33;

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void collison_bullet_block(SDL_Rect &rect,SDL_Rect &rect2,SDL_Rect &rect3){
    if(rect.x>1110 || rect.y > 810){
            rect.y = rect3.y  + 100;
            rect.x = 25;
            canon_speed_y = 0;
            canon_speed_x = 0;
    }

    if(((rect.x+rect.w >=rect2.x-5) &&(rect.x+rect.w<=rect2.x+rect2.w))&&((rect.y+rect.h>=rect2.y) &&(rect.y+rect.h<=rect2.y+rect2.h+8))){
         canon_speed_y = -30;
         canon_speed_x = -10;
         count_shoot--;
         display_shoot_and_point_counter();
    }

}

void collison_bullet_king(SDL_Rect &rect,SDL_Rect &rect2,SDL_Rect &rect3){

     int random_positon_x = 850+(rand()%210);
     int random_positon_y = 80+(rand()%250);
     if(rect.x>1110 || rect.y > 810){
            rect.y = rect3.y  + 100;
            rect.x = 25;
            canon_speed_y = 0;
            canon_speed_x = 0;


    }
    if(((rect.x+rect.w >=rect2.x-5) &&(rect.x+rect.w<=rect2.x+rect2.w))&&((rect.y+rect.h>=rect2.y) &&(rect.y+rect.h<=rect2.y+rect2.h+8))){
         canon_speed_y = -30;
         canon_speed_x = -10;
         rect2.x = random_positon_x;
         rect2.y = random_positon_y;
         count_shoot+=2;
         points++;
         display_shoot_and_point_counter();

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

        if(rect.y < 250){
                rect.y +=0;
            }

        else{
                rect.y -=5;
            }
        }

    if (key_state[SDL_SCANCODE_DOWN]){

         if(rect.y < 615){
                rect.y +=5;
            }
        else{

                rect.y -=0;
            }
    }

    if(rect2.x <150 ){

        if (key_state[SDL_SCANCODE_P]){

                if(canon_power_shoot_y >10){
                    canon_power_shoot_x += 0;
                    canon_power_shoot_y += 0;
                }
                else{
                    canon_power_shoot_x += 2.5;
                    canon_power_shoot_y += 1;
                }


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
        rect2.y = rect.y + 100;
        rect2.x = 15;
        canon_speed_y = 0;
        canon_speed_x = 0;

    }

    return true;
}

void display_shoot_and_point_counter(){
    std::cout <<"Shoots: "<<count_shoot<<"   Points: "<<points<<std::endl;
    if(count_shoot<=0){
         std::cout <<"GAME OVER"<<std::endl;
         SDL_DestroyWindow(window);
         SDL_Quit();

    }

}





