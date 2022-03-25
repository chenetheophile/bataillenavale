#include <gtk/gtk.h>
#include "../header/repriseJeu.h"

extern int joueur,width,height;
extern GtkWidget*GameMenu,*copieJ1Bateau,*copieJ2Bateau;

/**< Montrer la grille copié. */

void montrerGrille(GtkWidget *widget, gpointer   data)
{

    gtk_container_remove(GTK_CONTAINER(GameMenu),GTK_WIDGET(gtk_bin_get_child(GTK_BIN(GameMenu))));
    if(joueur==1)
    {
        gtk_container_add(GTK_CONTAINER(GameMenu),copieJ1Bateau);
    }
    else if(joueur==2)
    {
        gtk_container_add(GTK_CONTAINER(GameMenu),copieJ2Bateau);
    }
    gtk_window_move(GTK_WINDOW(GameMenu),(int)width/4,(int)height/4);
    g_signal_connect(G_OBJECT(GameMenu), "delete-event", G_CALLBACK(repriseJeu), NULL);
    gtk_widget_show_all(GTK_WIDGET(GameMenu));
}
