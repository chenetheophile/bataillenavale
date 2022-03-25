#include <gtk/gtk.h>

extern int width,height;
int diff=1;
GtkWidget *fenetrechoixDiff=NULL;

/**< Ces fonctions servent à choisir la difficultés du jeu en mode solo. Un pop up apparait pour que le joueur choisisse sa difficulté */

void fermerDiff()
{
    gtk_widget_destroy(fenetrechoixDiff);
}

void boutonFacile()
{
    diff=1;
    fermerDiff();
}
void boutonMoyen()
{
    diff=2;
    fermerDiff();
}
void boutonDifficile()
{
    diff=3;
    fermerDiff();
}

void choisirDiff()
{
    GtkWidget *Facile;
    GtkWidget *Moyen;
    GtkWidget *Difficile;
    GtkWidget *Annuler;
    int hauteurbouton=50,largeurbouton=100;

    GtkWidget *gridFenetre;
    gridFenetre=gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(gridFenetre),20);
    gtk_grid_set_column_spacing(GTK_GRID(gridFenetre),20);


    fenetrechoixDiff=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"N");
    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(fenetrechoixDiff)));
    gtk_window_resize(GTK_WINDOW(fenetrechoixDiff),500,500);


    Facile=gtk_button_new_with_label("Facile");
    Moyen=gtk_button_new_with_label("Moyen");
    Difficile=gtk_button_new_with_label("Difficile");
    Annuler=gtk_button_new_with_label("Annuler");

    for(int i=0; i<3; i++)
    {
        gtk_grid_insert_column(GTK_GRID(gridFenetre),0);
        gtk_grid_insert_row(GTK_GRID(gridFenetre),0);
    }

    gtk_widget_set_size_request(Facile,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Facile,0,1,1,1);
    g_signal_connect(Facile,"clicked",boutonFacile,NULL);

    gtk_widget_set_size_request(Moyen,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Moyen,1,0,1,1);
    g_signal_connect(Moyen,"clicked",boutonMoyen,NULL);

    gtk_widget_set_size_request(Difficile,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Difficile,2,1,1,1);
    g_signal_connect(Difficile,"clicked",boutonDifficile,NULL);

    gtk_widget_set_size_request(Annuler,largeurbouton,hauteurbouton);
    gtk_grid_attach(GTK_GRID(gridFenetre),Annuler,1,1,1,1);
    g_signal_connect(Annuler,"clicked",fermerDiff,NULL);

    gtk_container_add(GTK_CONTAINER(fenetrechoixDiff),gridFenetre);
    gtk_window_move(GTK_WINDOW(fenetrechoixDiff),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(fenetrechoixDiff);
    gtk_dialog_run(GTK_DIALOG(fenetrechoixDiff));
}

