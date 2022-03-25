#include <gtk/gtk.h>

extern GtkWidget* copieJ1Bateau,*copieJ2Bateau;
extern int nbPoste,phaseDeJeu,touche;

/**< Met a jour la grille inerte pour enlever la partie du bateau qui à été touché */

void modifgrilleCopie(int colonne,int ligne,int joueur)
{
    GtkWidget *image;
    if(nbPoste==1 &&phaseDeJeu==2 || nbPoste==2 && phaseDeJeu==3)
    {

        image=gtk_image_new_from_file("photo/plouf.png");
        if(touche==1)
        {
            image=gtk_image_new_from_file("photo/flamme.png");
        }
    }
    if(joueur==1)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ1Bateau),colonne, ligne)!=NULL)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(copieJ1Bateau),colonne,ligne));
            if(nbPoste==1 &&phaseDeJeu==2 || nbPoste==2 && phaseDeJeu==3)
            {
                gtk_grid_attach(GTK_GRID(copieJ1Bateau),image,colonne,ligne,1,1);
            }
        }
    }
    else if(joueur==2)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ2Bateau),colonne,ligne)!=NULL)
        {
            gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(copieJ2Bateau),colonne,ligne));
            if(nbPoste==1 &&phaseDeJeu==2 || nbPoste==2 && phaseDeJeu==3)
            {
                gtk_grid_attach(GTK_GRID(copieJ2Bateau),image,colonne,ligne,1,1);
            }
        }
    }

}
