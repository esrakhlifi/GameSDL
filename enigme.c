#include <stdio.h>
#include <stdlib.h>
#include "enigme.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>


/**************************GENERER*******************************/

void genererEnigme(enigme *e, char *nomfichier) 
{
  int num,i,carac;
  char texte[255];
 srand(time(NULL));

  FILE *f=fopen(nomfichier,"r");
if (f==NULL)
	printf("erreur de l ouverture\n");
else 
{
	i=0;
	do
	  {
		num=(rand()%15)+1; 
	  }while((num!=1) && (num!=6) && (num!=11)); 
	printf("%d\n",num);
	do 
	  {
		if (num!=1)
	  	{
	  	   do
		     {
 			 carac=fgetc(f);
		     }while (carac!='\n');
 	 	   i++;
 	 	   printf("%d\n ",i);
	  	}
	  }while((fgetc(f)!=EOF) && (i!=num-1));

	fgets(texte,255,f);
	strcpy(e->question,texte);

	fgets(texte,255,f);
	strcpy(e->reponse1,texte);

	fgets(texte,255,f);
	strcpy(e->reponse2,texte);

	fgets(texte,255,f);
	strcpy(e->reponse3,texte);

	fgets(texte,255,f);
	e->numrep=atoi(texte);
}
fclose(f);
}
/******************************AFFICHAGE***********************************/

void init_affichage(enigme *e)
{
     e->police=TTF_OpenFont("mechanik-Bold.ttf",17);
    e->back2=NULL;
    e->posback2.x = 0; 
    e->posback2.y = 0;
    e->posq.x=350;
    e->posq.y=260;
    e->posrep1.x=400;
    e->posrep1.y=320;
    e->posrep2.x=630;
    e->posrep2.y=320;
    e->posrep3.x=510;
    e->posrep3.y=403;

     e->back2 =IMG_Load("background_q.png");
    SDL_Color couleurNoir= {255,255,255};
    e->q =TTF_RenderText_Blended(e->police,e->question,couleurNoir);
    e->rep1 =TTF_RenderText_Blended(e->police,e->reponse1,couleurNoir);
    e->rep2 =TTF_RenderText_Blended(e->police,e->reponse2,couleurNoir);
    e->rep3 =TTF_RenderText_Blended(e->police,e->reponse3,couleurNoir);
    e->image_clock=IMG_Load("clock1.png");  

	e->pos_image_clock.x=50;
	e->pos_image_clock.y=15;
	
	e->single_Clock.w=57;
	e->single_Clock.h=81;
	e->single_Clock.x=0;
	e->single_Clock.y=0;

	e->clock_num=0;
}

void afficherEnigme(enigme e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.back2,NULL,screen,&(e.posback2));
        displayClock(e,screen);
    SDL_BlitSurface(e.q, NULL, screen, &(e.posq));
    SDL_BlitSurface(e.rep1, NULL, screen, &(e.posrep1));
    SDL_BlitSurface(e.rep2, NULL, screen, &(e.posrep2));
    SDL_BlitSurface(e.rep3, NULL, screen, &(e.posrep3));
}


/******************************RESOLUTION*******************************/

int resultat(int choix,enigme *e)
{
  if (choix==e->numrep)
	{

		return 1;
	}
  else 
	{
		return 0;
	}
}

void affichresultat(SDL_Surface *Vrai,SDL_Surface *Faux,SDL_Rect positionV,SDL_Rect positionF,SDL_Surface *screen,int choix,enigme e,int r)
{
Vrai=NULL,Faux=NULL;
positionV.x =  370 ;
positionV.y =  325 ; 
positionF.x =  370 ;
positionF.y =  325 ;
if (r==1)
  {
	Vrai =IMG_Load("win.png");
	SDL_BlitSurface(Vrai,NULL,screen,&positionV);
  }
else if (r==0)
  {
	Faux =IMG_Load("wrong.png");
	SDL_BlitSurface(Faux,NULL,screen,&positionF);
  }
}

void displayClock(enigme e,SDL_Surface *screen)
	{
		SDL_BlitSurface(e.image_clock,&(e.single_Clock), screen, &e.pos_image_clock);
	}

void animer(enigme *e)
	{
		 	
	if (e->clock_num >=0 && e->clock_num <8) {
	e->single_Clock.x=e->clock_num * e->single_Clock.w;
	e->clock_num++;
	}
	
	if ( e->clock_num == 8) {
	e->single_Clock.x=e->clock_num * e->single_Clock.w;
	e->clock_num=0;
	}
 
	 
}

int affichertemps(float elapsed_time, SDL_Surface *screen) {
    SDL_Color color_temp = {255, 255, 255};
    TTF_Font* police_time = NULL;
    police_time = TTF_OpenFont("OriginTech personal use.ttf", 23);
    if (police_time == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return 0;
    }
    char temp[100];
    int temps = 30000 - (int) elapsed_time * 1000; 
    if(temps < 0)
    {
        temps = 0;
    }
    int secondes = temps / 1000;
    int minutes = secondes / 60;
    secondes = secondes % 60;
    sprintf(temp, "%02d:%02d", minutes, secondes); 

 
    SDL_Surface* temps_surface = NULL;
    temps_surface = TTF_RenderUTF8_Solid(police_time, temp, color_temp);
    if (temps_surface == NULL) {
        fprintf(stderr, "Failed to create surface: %s\n", TTF_GetError());
        return 0;
    }

   
    SDL_Rect pos_temp;
    pos_temp.x = 100;
    pos_temp.y = 50;


    SDL_BlitSurface(temps_surface, NULL, screen, &pos_temp);
    
    SDL_FreeSurface(temps_surface);
    TTF_CloseFont(police_time);


    if (temps == 0) {
        return 1;
    } else {
        return 0;
    }
}

void initialiser_image2(enigme *imgsecond)
{
	imgsecond->url="Timesup.jpg";
	imgsecond->img=IMG_Load(imgsecond->url);
	if (imgsecond->img == NULL)
	{
		printf("unable to load background image %s\n",SDL_GetError());
		return;
	}
	imgsecond->pos_img_affiche.x=0;
	imgsecond->pos_img_affiche.y=0;
	imgsecond->pos_img_affiche.h=864;
	imgsecond->pos_img_affiche.w=1152;
	imgsecond->pos_img_ecran.x=0;
	imgsecond->pos_img_ecran.y=0;
}

void afficher_image2(SDL_Surface *screen,enigme imgsecond)
{
	SDL_BlitSurface(imgsecond.img,NULL,screen,&imgsecond.pos_img_ecran);
}

