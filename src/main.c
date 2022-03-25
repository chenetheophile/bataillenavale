#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <winsock2.h>

#include "../header/faireMenu.h"
/*
Une fois que Gtk et SDL2 sont installé :
Pour le Linker mettre tous les fichiers dll présent dans le dossier dll.a
Aussi dans le linker dans other options mettre :
-lmingw32
-lSDL2main
-lSDL2
-lSDL2_mixer

*/
int width;
int height;

GtkWidget *Menu=NULL,*Option=NULL,*Joue=NULL;
int t1, t2, joueur, consec = 0, dir, lp, cp, l1, c1, essais;
int plateauBateauJ1[11][11]= {0},plateauBateauJ2[11][11]= {0},plateauTirJ1[11][11]= {0},plateauTirJ2[11][11]= {0};
int longueur[6] = {5,4,3,3,2,1};
char* navires[5] = {"porte-avion (5 cases)", "croiseur (4 cases)", "contre-torpilleur (3 cases)", "sous-marin (3 cases)", "torpilleur (2 cases)"};

int main(int argc, char **argv)
{

    gtk_init(&argc,&argv);
    SDL_Init(SDL_INIT_AUDIO);

    joueur = 1;
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

    faireMenu();

    gtk_main();
    Mix_CloseAudio();

    return 0;
}
