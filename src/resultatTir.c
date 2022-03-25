#include <gtk/gtk.h>
#include <SDL2/SDL_mixer.h>

#define WAV_PATH1 "son/plouf.wav"
#define WAV_PATH2 "son/kaboom.wav"

extern GtkWidget*grilleJ1Tir,*grilleJ2Tir,*Joue;

/**< Affiche un message si le tir fait mouche ou pas.
Joue un son en conséquence et affihce une image en relation avec la touche. Eau pour plouf et feu pour toucher
 */

void resultatTir(int ligne,int colonne,int toucher,int joueur)
{
    GtkWidget *image;
    Mix_Chunk *bruit=NULL;

    image=gtk_image_new_from_file("photo/plouf.png");
    if(toucher==1)
    {
        image=gtk_image_new_from_file("photo/flamme.png");
        bruit = Mix_LoadWAV(WAV_PATH2);
    }
    else
    {

        bruit = Mix_LoadWAV(WAV_PATH1);
    }
    Mix_PlayChannel(1, bruit, 0);

    if(joueur==1)
    {

        gtk_grid_attach(GTK_GRID(grilleJ1Tir),image,colonne,ligne,1,1);

    }
    else if(joueur==2)
    {
        gtk_grid_attach(GTK_GRID(grilleJ2Tir),image,colonne,ligne,1,1);


    }
    int id=g_timeout_add(5,G_SOURCE_FUNC(Mix_FreeChunk),bruit);

    g_source_remove(id);
}
