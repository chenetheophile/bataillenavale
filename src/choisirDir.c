#include <gtk/gtk.h>

#include "../header/fermeFenetre.h"

extern int width,height;
int direction;
GtkWidget *fenetrechoix=NULL;

/**< Fonction qui permet a l'utilisateur de choisir une direction lorsqu'il pose un bateau.  */

void boutonHaut()
{
    direction=1;
}
void boutonBas()
{
    direction=2;
}
void boutonGauche()
{
    direction=3;
}
void boutonDroite()
{
    direction=4;
}
void fermerDir()
{
    gtk_widget_destroy(fenetrechoix);
}

void choisirDir()
{


    direction=-1;
    GtkWidget *Haut;
    GtkWidget *Bas;
    GtkWidget *Gauche;
    GtkWidget *Droite;
    GtkWidget *Annuler;
    int hauteurbouton=50,largeurbouton=100;

    GtkWidget *gridFenetre;
    gridFenetre=gtk_grid_new();
    fenetrechoix=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"N");
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(fenetrechoix)));
    gtk_window_resize(GTK_WINDOW(fenetrechoix),500,500);

    Haut=gtk_button_new_with_label("Haut");
    Bas=gtk_button_new_with_label("Bas");
    Gauche=gtk_button_new_with_label("Gauche");
    Droite=gtk_button_new_with_label("Droite");
    Annuler=gtk_button_new_with_label("Annuler");

    for(int i=0; i<3; i++)
    {
        gtk_grid_insert_column(GTK_GRID(gridFenetre),0);
        gtk_grid_insert_row(GTK_GRID(gridFenetre),0);
    }

    gtk_widget_set_size_request(Haut,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Haut,1,0,1,1);
    g_signal_connect(Haut,"clicked",boutonHaut,NULL);
    g_signal_connect(Haut,"clicked",G_CALLBACK(fermerDir),NULL);

    gtk_widget_set_size_request(Bas,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Bas,1,2,1,1);
    g_signal_connect(Bas,"clicked",boutonBas,NULL);
    g_signal_connect(Bas,"clicked",G_CALLBACK(fermerDir),NULL);

    gtk_widget_set_size_request(Gauche,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Gauche,0,1,1,1);
    g_signal_connect(Gauche,"clicked",boutonGauche,NULL);
    g_signal_connect(Gauche,"clicked",G_CALLBACK(fermerDir),NULL);

    gtk_widget_set_size_request(Droite,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Droite,2,1,1,1);
    g_signal_connect(Droite,"clicked",boutonDroite,NULL);
    g_signal_connect(Droite,"clicked",G_CALLBACK(fermerDir),NULL);

    gtk_widget_set_size_request(Annuler,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Annuler,1,1,1,1);
    g_signal_connect(Annuler,"clicked",G_CALLBACK(fermerDir),NULL);

    gtk_container_add(GTK_CONTAINER(fenetrechoix),gridFenetre);
    gtk_window_move(GTK_WINDOW(fenetrechoix),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(fenetrechoix);
    gtk_dialog_run(GTK_DIALOG(fenetrechoix));
}

