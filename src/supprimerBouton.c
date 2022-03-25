#include <gtk/gtk.h>

extern int joueur,phaseDeJeu,nbPoste;
extern GtkWidget*grilleJ1Bateau,*grilleJ2Bateau,*grilleJ1Tir,*grilleJ2Tir;

/**< Enleve un bouton de la grille que ce soit pour un bateau ou un tir */

void supprimerBouton(int ligne,int colonne)
{
    if(nbPoste==1)
    {
        if(phaseDeJeu==1)
        {
            if(joueur==1)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ1Bateau),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ1Bateau),ligne,colonne));
                }
            }
            else if(joueur==2)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ2Bateau),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ2Bateau),ligne,colonne));
                }
            }
        }
        else if(phaseDeJeu==2)
        {
            if(joueur==1)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ1Tir),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ1Tir),ligne,colonne));
                }
            }
            else if(joueur==2)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ2Tir),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ2Tir),ligne,colonne));
                }
            }
        }
    }
    else
    {
        if(phaseDeJeu==2)
        {
            if(joueur==1)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ1Bateau),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ1Bateau),ligne,colonne));
                }
            }
            else if(joueur==2)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ2Bateau),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ2Bateau),ligne,colonne));
                }
            }
        }
        else if(phaseDeJeu==3)
        {
            if(joueur==1)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ1Tir),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ1Tir),ligne,colonne));
                }
            }
            else if(joueur==2)
            {
                if(gtk_grid_get_child_at(GTK_GRID(grilleJ2Tir),ligne,colonne)!=NULL)
                {
                    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(grilleJ2Tir),ligne,colonne));
                }
            }
        }

    }
}
