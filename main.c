#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "fonction.h"



int main(int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
SDL_Surface* screen = SDL_SetVideoMode(1500, 500, 32, SDL_SWSURFACE);
    Minimap minimap;
    init_minimap(&minimap);
  
    Uint32 start_time = SDL_GetTicks();
    
    SDL_Surface* background = IMG_Load("back.png");
    SDL_Surface* player = IMG_Load("perso.png");
    SDL_Surface* masque = IMG_Load("backmask.png");

   
    SDL_Rect player_pos = {10, 360, 0, 0};

  
   
    SDL_Event event;
    int running = 1;
    while (running) {
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            player_pos.y -= 10;
                            if (collisionPP(player_pos, masque)) {
                                player_pos.y += 10; 
                            }
                            break;
                        case SDLK_DOWN:
                            player_pos.y += 10;
                            if (collisionPP(player_pos, masque)) {
                                player_pos.y -= 10;
                            }
                            break;
                        case SDLK_LEFT:
                            player_pos.x -= 10;
                            if (collisionPP(player_pos, masque)) {
                                player_pos.x += 10;
                            }
                            break;
                        case SDLK_RIGHT:
                            player_pos.x += 10;
                            if (collisionPP(player_pos, masque)) {
                                player_pos.x -= 10;
                            }
                            break;
                    }
                    break;
            }
        }

        
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - start_time;

        
        SDL_BlitSurface(background, NULL, screen, NULL);
        SDL_BlitSurface(player, NULL, screen, &player_pos);

        
        MAJMinimap(player_pos, &minimap, player_pos, 11);

        
        
        afficher_minimap(minimap, screen);
        affichertempsen(elapsed_time / 1000);
        affichertemps(elapsed_time / 1000);
        animerMinimap(&minimap);
        animerMinimape(&minimap);
         
        
        SDL_Flip(screen);
    }

    
    SDL_FreeSurface(background);
    SDL_FreeSurface(player);
    SDL_FreeSurface(masque);
    liberer_minimap(&minimap);
    TTF_Quit();
    SDL_Quit();

    return 0;
}



