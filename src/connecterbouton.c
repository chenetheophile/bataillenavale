#include <gtk/gtk.h>

#include "../header/phasePlacement.h"
#include "../header/phaseTir.h"

extern int phaseDeJeu,joueur;
extern GtkWidget*grilleJ1Bateau,*grilleJ2Bateau,*grilleJ1Tir,*grilleJ2Tir;

/**< Cette fonction sert a connecter les boutons de toutes les grilles de jeu. Elle connecte
les grille de bateau au fonction de placement de bateau et les fonctions de tir pour les grilles de tir */

void connecterbouton()
{
    GtkWidget*bouton;
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            bouton=gtk_grid_get_child_at(GTK_GRID(grilleJ1Bateau),i,j);
            g_signal_connect(bouton,"clicked",G_CALLBACK(phasePlacement),grilleJ1Bateau);

        }
    }

    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            bouton=gtk_grid_get_child_at(GTK_GRID(grilleJ2Bateau),i,j);
            g_signal_connect(bouton,"clicked",G_CALLBACK(phasePlacement),grilleJ2Bateau);
        }
    }


    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            bouton=gtk_grid_get_child_at(GTK_GRID(grilleJ1Tir),i,j);
            g_signal_connect(bouton,"clicked",G_CALLBACK(phaseTir),grilleJ1Tir);
        }
    }

    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            bouton=gtk_grid_get_child_at(GTK_GRID(grilleJ2Tir),i,j);
            g_signal_connect(bouton,"clicked",G_CALLBACK(phaseTir),grilleJ2Tir);
        }

    }
}

