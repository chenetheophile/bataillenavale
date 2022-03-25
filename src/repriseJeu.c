#include <gtk/gtk.h>

extern int joueur;
extern GtkWidget*GameMenu,*copieJ1Bateau,*copieJ2Bateau;

/**< Revenir au jeu lorsque copie de la grille de bateau a été affiché */

void repriseJeu(GtkWidget *widget, gpointer   data)
{

    if(gtk_bin_get_child(GTK_BIN(GameMenu))!=NULL)
    {
        if(joueur==1)
        {
            copieJ1Bateau=g_object_ref(copieJ1Bateau);
            gtk_container_remove(GTK_CONTAINER(GameMenu),copieJ1Bateau);
        }
        if(joueur==2)
        {
            copieJ1Bateau=g_object_ref(copieJ2Bateau);
            gtk_container_remove(GTK_CONTAINER(GameMenu),copieJ2Bateau);
        }
    }
    gtk_window_close(GTK_WINDOW(GameMenu));

}
