#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct
{
char question[200];
char reponse1[200]; 
char reponse2[200];
char reponse3[200]; 
int numrep; 
SDL_Surface *back2; 
SDL_Rect posback2; 
SDL_Surface *q,*rep1,*rep2,*rep3; 
SDL_Rect posq,posrep1,posrep2,posrep3;  
SDL_Surface *repp1,*repp2,*repp3; 
SDL_Rect posrepp1,posrepp2,posrepp3;  
TTF_Font *police; 
SDL_Surface *image_clock;  
SDL_Rect pos_image_clock;  
SDL_Rect single_Clock; 
int clock_num; 
char *url; 
SDL_Rect pos_img_affiche; 
	SDL_Rect pos_img_ecran; 
	SDL_Surface *img; 
}enigme;




void genererEnigme(enigme * e, char *nomfichier);

void init_affichage(enigme *e);
void afficherEnigme(enigme e, SDL_Surface *screen);
int resultat(int choix,enigme *e);
void affichresultat(SDL_Surface *Vrai,SDL_Surface *Faux,SDL_Rect positionV,SDL_Rect positionF,SDL_Surface *screen,int choix,enigme e,int r);
void displayClock(enigme e,SDL_Surface *screen);
void animer(enigme *e);
int affichertemps(float elapsed_time, SDL_Surface *screen);
void initialiser_image2(enigme *imgsecond);
void afficher_image2(SDL_Surface *screen,enigme imgsecond);
void afficherepp1(enigme e, SDL_Surface *screen);
void afficherepp2(enigme e, SDL_Surface *screen);
void afficherepp3(enigme e, SDL_Surface *screen);
