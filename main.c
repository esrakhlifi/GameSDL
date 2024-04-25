#include <stdio.h>
#include <stdlib.h>
#include "enigme.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#define FRAME_TIME 16 

int main(int argc, char* argv[])
{
int continuer=1;
SDL_Surface *screen=NULL;
enigme e;
SDL_Surface *img; 
enigme imgsecond;
char nomfichier[]="enigme.txt";
int choix,run,r=-1,aff=0;
SDL_Surface *Vrai, *Faux;
SDL_Rect positionV, positionF;
Uint32 frame_count = 0;
Uint32 game_start_time = 0;
Uint32 frame_start_time = 0;
Uint32 start_time = 0;
float elapsed_time = 0.0;
Uint32 elapsed_frames = 0;
TTF_Font* font = NULL;
int xdd=0;
TTF_Init();
screen=SDL_SetVideoMode(1100, 727, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);  
SDL_WM_SetCaption("Enigme", NULL);

genererEnigme(&e,nomfichier);

init_affichage(&e);
initialiser_image2(&imgsecond);
while(continuer)
{
	Uint32 start_time = SDL_GetTicks();
	float elapsed_time = (start_time - game_start_time) / 1000.0;
	afficherEnigme(e,screen);
	afficher_image2(screen,imgsecond);          			
  }
      affichertemps(elapsed_time,screen);
  
	if(aff==1)
		{
			SDL_Delay(2000);
			continuer=0;	
		}
		if(aff==2)
		{
			SDL_Delay(2000);
			continuer=0;	
		}
		if(aff==3)
		{	
			SDL_Delay(2000);
			continuer=0;	
		}
		if(aff==4)
		{
			continuer=0;	
		}
   SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
	   case SDL_QUIT:
		continuer=0;
	    break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
               		 case SDLK_a:
                    	   choix = 1;
                         break;
               		 case SDLK_b:
                           choix = 2;
                  	  break;
               		 case SDLK_c:
                  	   choix =3;
                  	  break;
		}
	    break; 
	      case SDL_MOUSEBUTTONUP: 
          if (event.button.button==SDL_BUTTON_LEFT &&(event.motion.y<=347 && event.motion.y>=307
          					     && event.motion.x<=529 && event.motion.x>=348))
            {
	choix = 1;
            
            }			 
            if (event.button.button==SDL_BUTTON_LEFT &&(event.motion.y<=350 && event.motion.y>=307
          					     && event.motion.x<=764 && event.motion.x>=582))
            {
	choix = 2;
            
            }	
            if (event.button.button==SDL_BUTTON_LEFT &&(event.motion.y<=432 && event.motion.y>=389
          					     && event.motion.x<=641 && event.motion.x>=459))
            {
	choix = 3;
            
            }	
 	break; 
 
 	}
  	 if (choix==1)
		{	
			r=resultat(choix,&e);
			
			aff=1;
		}
		if (choix==2)
		{
		r=resultat(choix,&e);
			aff=2;
		}
		if (choix==3)
		{
		r=resultat(choix,&e);
			aff=3;
		}
	
	   affichresultat(Vrai,Faux,positionV,positionF,screen,choix,e,r);
	   
   SDL_Flip(screen);
  
}
 animer(&e);
 SDL_Delay(150);
 SDL_Flip(screen);
if (elapsed_time >= 30.0) { 
	continuer=0;
            }
Uint32 elapsed_frames = SDL_GetTicks() - frame_start_time;
if (elapsed_frames < frame_start_time) {
        SDL_Delay(FRAME_TIME - elapsed_frames);
    }
frame_start_time = SDL_GetTicks();

TTF_Quit;
//SDL_Quit;
return EXIT_SUCCESS;
}


